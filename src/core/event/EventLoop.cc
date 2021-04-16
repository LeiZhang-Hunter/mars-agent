//
// Created by zhanglei on 2021/4/5.
//

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

    //管道事件触发
    auto channel = static_cast<Channel *>(args);
    channel->setEvents(events);
    channel->handelEvent();
}

bool Event::EventLoop::eventSet(const std::shared_ptr<Channel>& channel) {

    //
    struct event* eventFd = event_new(base, channel->getChannelFd(), channel->getEvents(), onEvent,
                                      static_cast<void *>(channel.get()));

    struct timeval time;
    time.tv_sec = channel->getTimer().tv_sec;
    time.tv_usec = channel->getTimer().tv_usec;
    int ret = event_add(eventFd, &time);
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

    if (ret == 1) {
    }
}