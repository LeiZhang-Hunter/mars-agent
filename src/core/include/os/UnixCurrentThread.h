//
// Created by zhanglei on 2021/5/2.
//

#ifndef MARS_AGENT_UNIXCURRENTTHREAD_H
#define MARS_AGENT_UNIXCURRENTTHREAD_H
#include <memory>
#include <unistd.h>
#include <sys/syscall.h>

#include "event/EventLoop.h"

namespace OS {

    namespace UnixCurrentThread {
        extern __thread int t_cachedTid;

        extern __thread Event::EventLoop* currentLoop;

        inline int tid()
        {
            if (__builtin_expect(t_cachedTid == 0, 0))
            {
                t_cachedTid = syscall(SYS_gettid);
            }
            return t_cachedTid;
        }

        inline Event::EventLoop* loop()
        {
            return currentLoop ;
        }
    }


};

#endif //MARS_AGENT_UNIXCURRENTTHREAD_H
