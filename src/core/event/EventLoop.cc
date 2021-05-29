//
// Created by zhanglei on 2021/4/5.
//
extern "C" {
#include <event2/buffer.h>
#include <event.h>
}
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

bool Event::EventLoop::deleteChannel(const std::shared_ptr<Channel>& channel)
{
    //这里不要加锁，不要发生竞争关系
    ChannelMap::iterator it;

    it = channels.find(channel->getChannelFd());

    if (it != channels.end()) {
        channels.erase(it);
        return true;
    }
    return false;
}

bool Event::EventLoop::deleteChannelByFd(int fd)
{
    //这里不要加锁，不要发生竞争关系
    ChannelMap::iterator it;

    it = channels.find(fd);

    if (it != channels.end()) {
        channels.erase(it);
        std::cout << "delete channels" << std::endl;
        return true;
    }
    return false;
}

void Event::EventLoop::onRead(bufferevent* evClient, void* arg) {
    //管道事件触发
    auto channel = static_cast<Channel *>(arg);
    EventCallable callable = channel->getOnReadCallable();
    if (callable) {
        callable(evClient, channel);
    }
}

void Event::EventLoop::onWrite(bufferevent* evClient, void* arg) {

}

void Event::EventLoop::onEvent(bufferevent* ev, short flag, void* arg) {

    //管道不能是空的
    if (!arg)
        return;

    //管道事件触发
    auto channel = static_cast<Channel *>(arg);

    if (flag & BEV_OPT_CLOSE_ON_FREE) {
        channel->close(ev, channel);
    }
//    channel->handelEvent(flag);
}

bool Event::EventLoop::eventSet(const std::shared_ptr<Channel>& channel) {
    std::cout << "eventSet" << std::endl;
    //
    //添加新事件
    struct bufferevent *client;
    client = bufferevent_socket_new(base, channel->getChannelFd(), BEV_OPT_CLOSE_ON_FREE);

    int ret = 0;
    if (channel->getTimer().tv_usec > 0) {
        struct timeval time;

        time.tv_sec = channel->getTimer().tv_sec;
        time.tv_usec = channel->getTimer().tv_usec;
        bufferevent_set_timeouts(client, &time, nullptr);
    }
    std::cout << channel->getChannelFd() << std::endl;
    bufferevent_setcb (client, onRead, onWrite, onEvent,  static_cast<void *>(channel.get()));
    bufferevent_enable (client, channel->getEvents());
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