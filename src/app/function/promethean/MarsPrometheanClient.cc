//
// Created by zhanglei on 2021/5/9.
//
extern "C" {
#include <event2/buffer.h>
#include <event.h>
}

#include "common/MarsJson.h"

#include <string>

#include <iostream>
#include "os/UnixCurrentThread.h"
#include "promethean/MarsPrometheanConfig.h"
#include "promethean/MarsPrometheanClient.h"
#include "promethean/MarsPrometheanObject.h"
#include "promethean/BizPrometheanObject.h"
#include "promethean/MarsHttpStandardPrometheanObject.h"

using namespace function;

promethean::MarsPrometheanClient::MarsPrometheanClient(int fd, const std::shared_ptr<MarsPrometheanObject> &object,
                                                       const std::shared_ptr<MarsPrometheanConfig> &config) {
    clientFd = fd;
    bizParser = std::make_shared<BizPrometheanObject>(object);
    httpParser = std::make_shared<MarsHttpStandardPrometheanObject>(object);
    maxBufferSize = config->getClientBufferSize();

}

void promethean::MarsPrometheanClient::setWheelPtr(const Event::timingWheelPtr &wheelPtr_) {
    wheelPtr = wheelPtr_;
    {
        Event::timingWheelObjectPtr wheelObject(new Event::TimingWheelObject(shared_from_this()));
        Event::timingWheelObjectWeakPtr weakPtr(wheelObject);
        wheelClientWeakPtr = weakPtr;
        wheelPtr->add(wheelObject);
    }
    return;
//    shared_ptr<function::promethean::timingWheelClientObjectStruct>
}

void promethean::MarsPrometheanClient::onRead(struct bufferevent *bev, void *ctx) {
    char msg[BUFSIZ];

    if (wheelPtr) {
        Event::timingWheelObjectPtr wheelObject(wheelClientWeakPtr.lock());
        if (wheelObject) {
            wheelPtr->add(wheelObject);
        }
    }

    while (runStatus) {
        size_t readSize = bufferevent_read(bev, &msg, 2);

        //数据读完了
        if (readSize <= 0)
            break;

        msg[readSize] = '\0';
        std::string data(msg);
        parse(data);
    }
    std::cout << count << std::endl;
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
    std::cout << "use_count:" << shared_from_this().use_count() << std::endl;
}

void promethean::MarsPrometheanClient::parse(std::string &data) {

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

//        Json::Value prometheanValue;
//        //对json进行编码
//        jsonTool->jsonDecode(content, &prometheanValue);
        //检查第一个字节
        switch (action) {
            case '0':
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