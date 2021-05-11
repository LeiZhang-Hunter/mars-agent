//
// Created by zhanglei on 2021/5/9.
//
extern "C" {
#include <event2/buffer.h>
#include <event.h>
}
#include <iostream>
#include "promethean/MarsPrometheanClient.h"
#include "os/UnixCurrentThread.h"
using namespace function;
void promethean::MarsPrometheanClient::onRead(struct bufferevent *bev, void *ctx) {
    char msg[1024];
    size_t readSize = bufferevent_read(bev, &msg, sizeof(msg));
    msg[readSize] = '\0';
    std::cout << OS::UnixCurrentThread::tid() << msg << std::endl;
}