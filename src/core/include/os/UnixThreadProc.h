//
// Created by zhanglei on 2020/11/14.
//

#ifndef PHPLOGGUARD_UNIXTHREADPROC_H
#define PHPLOGGUARD_UNIXTHREADPROC_H

#include "Callable.h"
#include "os/UnixCountDownLatch.h"
#include "os/UnixSignalDescription.h"

namespace OS {
    class UnixThreadProc {
    public:
        /**
         * 初始化线程
         * @param loop_
         */
        UnixThreadProc(const std::shared_ptr<Event::EventLoop> &loop_,
                       std::shared_ptr<UnixCountDownLatch> &latch_) : latch(latch_) {
            loop = loop_;
        }

        void onStop();

        //运行线程空间主程序
        void runThread();

        pid_t getThreadTid() {
            return threadTid;
        }

        void setInitCallable(const Callable::initCallable &callable) {
            threadInitCallable = callable;
        }

    private:
        //事件循环
        std::shared_ptr<Event::EventLoop> loop;

        std::shared_ptr<UnixCountDownLatch> &latch;
        //线程id
        pid_t threadTid;

        //线程初始化的回调
        Callable::initCallable threadInitCallable;
    };
}

#endif //PHPLOGGUARD_UNIXTHREADPROC_H
