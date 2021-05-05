//
// Created by zhanglei on 2021/5/1.
//

#ifndef MARS_AGENT_UNIXTHREADCONTAINER_H
#define MARS_AGENT_UNIXTHREADCONTAINER_H

#include <memory>
#include <vector>
#include "Callable.h"
#include "Noncopyable.h"

namespace OS {

    class UnixThread;

    class UnixThreadContainer : public Noncopyable, public std::enable_shared_from_this<UnixThreadContainer> {
    public:
        UnixThreadContainer();

        void setThreaderNumber(int number) {
            if (number > 0) {
                threadNumber = number;
            }
        }

        void setThreadInitCallable(const Callable::initCallable& callable) {
            initClosure = callable;
        }

        void task(const Callable::Task& task);

        void start();

        void stop();

        //检查线程是否已经注册
        ~UnixThreadContainer();

    private:

        Callable::initCallable initClosure;

        //派遣计数器
        unsigned short taskDispatcherCount = 0;

        //线程的启动数目
        unsigned short threadNumber;

        //线程派遣管理器
        std::vector<std::shared_ptr<UnixThread>> threadDispatcherManager;
    };
}


#endif //MARS_AGENT_UNIXTHREADCONTAINER_H
