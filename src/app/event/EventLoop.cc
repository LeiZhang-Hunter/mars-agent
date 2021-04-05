//
// Created by zhanglei on 2021/4/5.
//

#include "EventLoop.h"

void appEvent::EventLoop::quit() {
    if (!base) {
        return;
    }
    //循环、分发事件
    event_loopbreak();
}

void appEvent::EventLoop::loop() {
    if (!base) {
        return;
    }
    //循环、分发事件
    event_base_dispatch(base);
    printf("finish\n");
}