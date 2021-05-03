//
// Created by zhanglei on 2021/5/2.
//

#ifndef MARS_AGENT_EVENTQUEUE_H
#define MARS_AGENT_EVENTQUEUE_H

#include <functional>
#include <memory>
#include <queue>

#include "os/UnixMutex.h"
#include "Noncopyable.h"

namespace OS {
    class UnixMutex;
    class UnixThread;
}

namespace Event {
class EventQueue :public Noncopyable, public std::enable_shared_from_this<EventQueue>{
    public:

        EventQueue(const std::shared_ptr<OS::UnixThread>& threadObject);

        typedef std::function<void ()> Task;

        void pushTask(const Task& task);

        void dispatchTask();

        ~EventQueue() {

        }
    private:
        std::queue<Task> taskQueue;

        /**
         * 互斥锁
         */
        OS::UnixMutex mMutex;

        std::shared_ptr<OS::UnixThread> thread;

    };
}

#endif //MARS_AGENT_EVENTQUEUE_H
