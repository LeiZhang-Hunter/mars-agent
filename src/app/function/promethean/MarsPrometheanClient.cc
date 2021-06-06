//
// Created by zhanglei on 2021/5/9.
//
extern "C" {
#include <event2/buffer.h>
#include <event.h>
}
#include <string>
#include <mutex>
#include <iostream>
#include "os/UnixCurrentThread.h"
#include "common/MarsJson.h"
#include "promethean/MarsPrometheanConfig.h"
#include "promethean/MarsPrometheanClient.h"
#include "promethean/MarsPrometheanServer.h"

using namespace function;

promethean::MarsPrometheanClient::MarsPrometheanClient(int fd, const std::shared_ptr<MarsPrometheanObject> &object,
                                                       const std::shared_ptr<MarsPrometheanConfig> &config,
                                                       const std::shared_ptr<skywalking::MarsSkyWalking>& apmServer_,
                                                       const std::shared_ptr<BizPrometheanObject> &bizParser_,
                                                       const std::shared_ptr<MarsHttpStandardPrometheanObject> &httpParser_,
                                                       const Event::timingWheelPtr& wheelPtr_)
                                                       :apmServer(apmServer_),
                                                       bizParser(bizParser_),
                                                       httpParser(httpParser_),
                                                       wheelPtr(wheelPtr_) {
    clientFd = fd;
    maxBufferSize = config->getClientBufferSize();
}

void promethean::MarsPrometheanClient::onRead(struct bufferevent *bev, void *ctx) {
    char msg[BUFSIZ];

    if (wheelPtr) {
        Event::timingWheelObjectPtr wheelObject(wheelClientWeakPtr.lock());
        if (wheelObject) {
            wheelPtr->add(wheelObject);
        }
    }
    size_t left_len = evbuffer_get_length(bufferevent_get_input(bev));
    while (left_len) {
        size_t readSize = bufferevent_read(bev, &msg, BUFSIZ);
        //数据读完了
        if (readSize <= 0)
            break;
        left_len -= readSize;
        msg[readSize] = '\0';
        std::string data(msg);
        parse(bev, ctx, data);
    }
}

void promethean::MarsPrometheanClient::onClose(struct bufferevent *bev, Event::Channel *channel) {
    if (clientFd > 0) {
        clientFd = 0;
    }

    //关闭时间轮的对象
    if (wheelPtr) {
        Event::timingWheelObjectPtr wheelObject(wheelClientWeakPtr.lock());
        wheelPtr->clear(wheelObject);
        wheelObject.reset();
    }
}

void promethean::MarsPrometheanClient::close() {
    if (clientFd > 0) {
        ::close(clientFd);
        //解除绑定在channel上的链接
        Event::EventLoop* loop = OS::UnixCurrentThread::loop();
        loop->deleteChannelByFd(clientFd);
        clientFd = 0;
    }
}

void promethean::MarsPrometheanClient::reg(struct bufferevent *bev, void *ctx, const std::string& content) {
    std::string regInfo = apmServer->getRegInfo();
    regInfo = "a,b,c";
    if (!regInfo.empty()) {
        bufferevent_write(bev, regInfo.c_str(), regInfo.length());
        return;
    }

    Json::Value registerProtocol;

    try {
        common::MarsJson::jsonDecode(content, &registerProtocol);
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        return;
    }

    std::string appCode;
    try {
        appCode = registerProtocol["app_code"].asString();
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        return;
    }

    pid_t pid = 0;
    try {
        pid = registerProtocol["pid"].asUInt();
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        return;
    }

    try {
        std::string url = registerProtocol["url"].asString();
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        return;
    }

    try {
        std::string version = registerProtocol["version"].asString();
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        return;
    }
    //确实是否有已经生成成功
    regInfo = apmServer->getRegInfo();
    if (!regInfo.empty()) {
        bufferevent_write(bev, regInfo.c_str(), regInfo.length());
        return;
    }

    regInfo = apmServer->regSkyWalking(appCode, pid);
    if (!regInfo.empty()) {
        bufferevent_write(bev, regInfo.c_str(), regInfo.length());
        return;
    }
    bufferevent_write(bev, regInfo.c_str(), regInfo.length());
}

void promethean::MarsPrometheanClient::parse(struct bufferevent *bev, void *ctx, std::string &data) {

    if (buffer.empty()) {
        buffer = data;
    } else {
        buffer.append(data);
    }

    while (runStatus) {
        int position = buffer.find('\n');
        if (position == std::string::npos) {

            //检查缓冲区大小
            if (buffer.length() > maxBufferSize) {
                ::close(clientFd);
                break;
            }
            if (data.length() > maxBufferSize) {
                ::close(clientFd);
                break;
            }
            break;
        }

        //进行解包
        if ((position + 1) > buffer.length()) {
            break;
        }

        if ((position) > buffer.length()) {
            break;
        }

        std::string content = buffer.substr(0, position);

        char action = content[0];
        content = (content.c_str() + 1);

        //检查第一个字节
        switch (action) {
            case '0':
                reg(bev, ctx, content);
                break;
            case '1':
                httpParser->parser(content);
                break;
            case '2':
                bizParser->parser(content);
                break;
            default:
                break;
        }

        count++;
        buffer = buffer.substr(position + 1, buffer.length());
        if (buffer.empty()) {
            break;
        }
    }
}

promethean::MarsPrometheanClient::~MarsPrometheanClient() {
    promethean::connection--;
    std::cout << "~MarsPrometheanClient" << std::endl;
    buffer.clear();
}