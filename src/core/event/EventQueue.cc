//
// Created by zhanglei on 2021/5/2.
//

#include <memory>

#include "os/UnixAutoMutex.h"
#include "event/EventQueue.h"
#include "os/UnixThread.h"
#include "os/UnixCurrentThread.h"

Event::EventQueue::EventQueue(const std::shared_ptr<OS::UnixThread>& threadObject) {
    thread = threadObject;
}

void Event::EventQueue::dispatchTask() {
    //交换地址
    std::queue<Callable::Task> mainTaskQueue;
    {
        OS::UnixAutoMutex guard(mMutex);
        mainTaskQueue.swap(taskQueue);
    }

    //循环遍历
    while (!mainTaskQueue.empty()) {
        auto cb = mainTaskQueue.front();
        cb();
        mainTaskQueue.pop();
    }
}

void Event::EventQueue::pushTask(const Callable::Task &task) {
    if (OS::UnixCurrentThread::tid() == thread->getTid())
    {
        task();
    } else {
        {
            OS::UnixAutoMutex guard(mMutex);
            taskQueue.push(task);
        }

        //唤醒线程
        thread->wakeUp();
    }

}