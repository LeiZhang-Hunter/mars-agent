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

namespace Event {

    //管道的前置声明
    class Channel;

    //管道的map
    typedef std::map<int, std::shared_ptr<Channel>> ChannelMap;

    /**
     * 信号派遣的函数类型
     */
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

        /**
         * 更新管道
         * @param channel
         * @return
         */
        bool updateChannel(const std::shared_ptr<Channel>& channel);

        /**
         * 获取基础事件
         * @return
         */
        struct event_base *getEventBase()
        {
            return base;
        }

        static void onEvent(evutil_socket_t, short, void *);

        ~EventLoop() {

        };

    private:
        /**
         * 设置事件
         * @param operation
         * @param channel
         * @return
         */
        bool eventSet(const std::shared_ptr<Channel>& channel);

        //循环的基础指针
        struct event_base *base = nullptr;

        /**
         * 管道集合
         */
        ChannelMap channels;;
    };
}
#endif //MARS_AGENT_EVENTLOOP_H
