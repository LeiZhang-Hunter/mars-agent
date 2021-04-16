//
// Created by zhanglei on 2020/11/11.
//

#ifndef PHPLOGGUARD_CHANNEL_H
#define PHPLOGGUARD_CHANNEL_H


#include <sys/epoll.h>
#include <cstdint>
#include <memory>
#include <functional>

#include "event.h"

#include "Noncopyable.h"


namespace Event {
    typedef std::function<void()> EventCallable;

    class EventLoop;

    class Channel : public Noncopyable, public std::enable_shared_from_this<Channel> {
    public:
        //初始化线程之间通讯的管道
        Channel(const std::shared_ptr<EventLoop> &loop_, int fd) {
            loop = loop_;
            channelFd = fd;
            events = 0;
        }

        bool setOnReadCallable(const EventCallable &callable) {
            eventOnRead = callable;
            return true;
        }

        bool setOnCloseCallable(const EventCallable &callable) {
            eventOnClose = callable;
            return true;
        }

        bool setOnErrorCallable(const EventCallable &callable) {
            eventOnError = callable;
            return true;
        }

        bool setOnWriteCallable(const EventCallable &callable) {
            eventOnWrite = callable;
            return true;
        }

        bool setEvents(uint32_t _events) {
            return events = _events;
        }

        uint32_t getEvents() {
            return events;
        }

        int getChannelFd() {
            return channelFd;
        }

        //开启可读事件
        bool enableReading(double second) {
            time.tv_sec = 0;
            time.tv_usec = second * 1000 * 1000;
            events |= EV_READ;
            update();
            return true;
        }

        //禁用可读事件
        bool disableReading() {
            events &= ~EV_READ;
            update();
            return true;
        }

        bool enableWriting(double second) {
            time.tv_sec = 0;
            time.tv_usec = second * 1000 * 1000;
            events |= EV_WRITE;
            update();
            return true;
        }

        bool disableWriting() {
            events &= ~EV_WRITE;
            update();
            return true;
        }

        bool handelEvent();

        void update();

        struct timeval& getTimer() {
            return time;
        }
    private:
        int channelFd;
        std::shared_ptr<EventLoop> loop;
        unsigned char events = EV_PERSIST;
        EventCallable eventOnRead;
        EventCallable eventOnClose;
        EventCallable eventOnWrite;
        EventCallable eventOnError;
        //管道的超时时间
        struct timeval time;
    };
}


#endif //PHPLOGGUARD_CHANNEL_H
