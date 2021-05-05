//
// Created by zhanglei on 2021/5/3.
//

#include "os/UnixCurrentThread.h"

namespace OS {
    namespace UnixCurrentThread {
        __thread int t_cachedTid = 0;
    }
}