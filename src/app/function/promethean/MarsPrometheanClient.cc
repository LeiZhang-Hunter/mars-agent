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
#include "promethean/MarsPrometheanClient.h"
#include "promethean/MarsPrometheanObject.h"
#include "promethean/BizPrometheanObject.h"
#include "promethean/MarsHttpStandardPrometheanObject.h"

using namespace function;

promethean::MarsPrometheanClient::MarsPrometheanClient(int fd, const std::shared_ptr<MarsPrometheanObject>& object) {
    clientFd = fd;
    bizParser = std::make_shared<BizPrometheanObject>(object);
    httpParser = std::make_shared<MarsHttpStandardPrometheanObject>(object);
}

void promethean::MarsPrometheanClient::onRead(struct bufferevent *bev, void *ctx) {
    char msg[BUFSIZ];
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
            if (buffer.length() > 65535) {
                ::close(clientFd);
                break;
            }
            if (data.length() > 65535) {
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