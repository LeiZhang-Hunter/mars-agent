//
// Created by zhanglei on 2021/4/5.
//
#include <iostream>
#include "event/EventSignal.h"
#include "event/EventLoop.h"

Event::EventSignal::EventSignal(const std::shared_ptr<EventLoop> &event) {
    //初始化event
    loop = event;

    //初始化默认的信号槽
    signalHandlers[SIGTERM] = std::make_pair(sigStopHandle, this);
    signalHandlers[SIGPIPE] = std::make_pair(sigPipeHandle, this);
    signalHandlers[SIGSEGV] = std::make_pair(sigSigSegvHandle, this);


}

void Event::EventSignal::sigStopHandle(evutil_socket_t sig, short events, void *userData) {
    std::cout << "stop agent" << std::endl;

    //
}

//SIGPIPE信号需要忽略
void Event::EventSignal::sigPipeHandle(int sig, short events, void *userData) {
    return;
}

//SIGPIPE信号需要忽略
void Event::EventSignal::sigSigSegvHandle(evutil_socket_t sig, short events, void *userData) {

}

bool Event::EventSignal::bindEvent() {
    //已经绑定过了，不需要再次绑定
    if (isBind) {
        return false;
    }

    struct event *signal;
    struct event_base *base;

    base = loop->getEventBase();

    if (!base) {
        return false;
    }

    //循环信号槽
    auto begin = signalHandlers.begin();
    for (; begin != signalHandlers.end(); begin++) {
        signal = evsignal_new(base, begin->first,
                begin->second.first,
                begin->second.second);
        event_add(signal, nullptr);
    }

    //完成绑定
    isBind = true;
    return true;
}