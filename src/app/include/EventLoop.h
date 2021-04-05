//
// Created by zhanglei on 2021/4/5.
//

#ifndef MARS_AGENT_EVENTLOOP_H
#define MARS_AGENT_EVENTLOOP_H
extern "C" {
#include <event.h>
};

#include "EventSignal.h"
#include "Noncopyable.h"

namespace appEvent {

    typedef void(*dispatcherSignal)(evutil_socket_t sig, short events, void *param);

    class EventLoop : public Noncopyable {
    public:
        EventLoop() : base(event_init()) {};

        //添加信号
        bool sigAdd(int sigNo, dispatcherSignal handle, void *userData) {
            struct event *signale = evsignal_new(base, sigNo, handle, userData);
            event_add(signale, nullptr);
            return true;
        }

        //退出
        void quit();

        //事件循环
        void loop();

        struct event_base *getEventBase()
        {
            return base;
        }

        ~EventLoop() {

        };

    private:
        struct event_base *base = nullptr;
        std::shared_ptr<EventSignal> sigDispatcher;
    };
}
#endif //MARS_AGENT_EVENTLOOP_H
