//
// Created by zhanglei on 2020/11/14.
//

#include <syscall.h>

#include "event/EventLoop.h"
#include "os/UnixThreadProc.h"

void OS::UnixThreadProc::onStop() {
    loop->quit();
}

void OS::UnixThreadProc::runThread() {
    //初始化线程id
    threadTid = syscall(SYS_gettid);

    //注册了初始化函数则运行初始化函数
    if (threadInitCallable) {
        threadInitCallable(loop);
    }
    std::cout << "loop" << std::endl;

    //完成初始化通知主线程继续运行
    latch->down();


    //进行事件循环
    loop->loop();
    std::cout << "thread " << "1" << " end" << std::endl;

}