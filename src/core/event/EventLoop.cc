//
// Created by zhanglei on 2021/4/5.
//

#include <iostream>
#include <zconf.h>
#include "event/Channel.h"
#include "event/EventLoop.h"

//更新管道
bool Event::EventLoop::updateChannel(const std::shared_ptr<Channel> &channel) {
    //这里不要加锁，不要发生竞争关系
    ChannelMap::iterator it;

    it = channels.find(channel->getChannelFd());

    channels[channel->getChannelFd()] = channel;

    eventSet(channel);
    return true;
}

void Event::EventLoop::onEvent(evutil_socket_t fd, short events, void * args) {

    //管道不能是空的
    if (!args)
        return;

    char buf[100];
    read(fd, buf, sizeof(buf));
    //管道事件触发
    auto channel = static_cast<Channel *>(args);
//    channel->setEvents(events);
    channel->handelEvent();
}

bool Event::EventLoop::eventSet(const std::shared_ptr<Channel>& channel) {
    std::cout << "eventSet" << std::endl;
    //
    struct event* eventFd = event_new(base, channel->getChannelFd(), channel->getEvents(), onEvent,
                                      static_cast<void *>(channel.get()));
    int ret = 0;
    if (channel->getTimer().tv_usec > 0) {
        struct timeval time;
        time.tv_sec = channel->getTimer().tv_sec;
        time.tv_usec = channel->getTimer().tv_usec;
        ret = event_add(eventFd, &time);
    } else {
        ret = event_add(eventFd, nullptr);
    }
    return !ret;
}

void Event::EventLoop::quit() {
    if (!base) {
        return;
    }
    //循环、分发事件
    event_base_loopbreak(base);
}

void Event::EventLoop::loop() {
    if (!base) {
        return;
    }
    //循环、分发事件
    int ret = event_base_dispatch(base);
    std::cout << "finish loop:" << ret << std::endl;
    if (ret == 1) {
    }
}