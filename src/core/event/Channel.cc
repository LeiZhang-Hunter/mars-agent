//
// Created by zhanglei on 2020/11/11.
//

#include "event/Channel.h"
#include "event/EventLoop.h"

void Event::Channel::update() {
    loop->updateChannel(shared_from_this());
}

bool Event::Channel::handelEvent(short flag) {
    if (flag & BEV_OPT_CLOSE_ON_FREE) {
    }
//    /**
//     * EPOLLIN 判断刻度
//     * EPOLLPRI 判断外带数据
//     * EPOLLRDHUP 对端关闭或者写一方关闭
//     */
//    if (events & (EV_READ)) {
//        if (eventOnRead) eventOnRead();
//    }
//
//    if (events & EV_WRITE) {
//        if (eventOnWrite) eventOnWrite();
//    }
    return true;
}

void Event::Channel::close(bufferevent* evClient, void* arg) {
    if (eventOnClose)
        eventOnClose(evClient, arg);

    loop->deleteChannel(shared_from_this());
}