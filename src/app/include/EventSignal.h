//
// Created by zhanglei on 2021/4/5.
//

#ifndef MARS_AGENT_EVENTSIGNAL_H
#define MARS_AGENT_EVENTSIGNAL_H

extern "C" {
#include <event.h>
};

#include <memory>
#include <map>
#include <csignal>
#include "Noncopyable.h"

namespace appEvent {
    //事件循环的前置声明
    class EventLoop;

    //信号处理器的函数指针类型
    typedef void(*signalHandle)(evutil_socket_t sig, short events, void *param);

    typedef std::map<int, std::pair<signalHandle, void *>> sigHandleMap;

    class EventSignal {
    public:
        EventSignal(const std::shared_ptr<EventLoop> &event);

        //停止处理的逻辑程序
        static void sigStopHandle(evutil_socket_t sig, short events, void *param);

        //写入错误的处理程序
        static void sigPipeHandle(evutil_socket_t sig, short events, void *param);

        //段错误的信号处理
        static void sigSigSegvHandle(evutil_socket_t sig, short events, void *param);

        //信号处理槽里添加处理信号
        bool setSignal(int sigNo, signalHandle handle, void* userData) {
            signalHandlers[sigNo] = std::make_pair(handle, userData);
            return true;
        }

        bool bindEvent();

        ~EventSignal() {};

    private:
        std::shared_ptr<EventLoop> loop;

        sigHandleMap signalHandlers;

        bool isBind = false;
    };
}
#endif //MARS_AGENT_EVENTSIGNAL_H
