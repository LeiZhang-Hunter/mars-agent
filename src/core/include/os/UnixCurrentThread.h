//
// Created by zhanglei on 2021/5/2.
//

#ifndef MARS_AGENT_UNIXCURRENTTHREAD_H
#define MARS_AGENT_UNIXCURRENTTHREAD_H

#include <unistd.h>

namespace OS {

    namespace UnixCurrentThread {
        extern __thread int t_cachedTid;

        inline int tid()
        {
            if (__builtin_expect(t_cachedTid == 0, 0))
            {
                t_cachedTid = syscall(SYS_gettid);
            }
            return t_cachedTid;
        }
    }


};

#endif //MARS_AGENT_UNIXCURRENTTHREAD_H
