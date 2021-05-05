//
// Created by zhanglei on 2021/5/1.
//

#include "os/UnixThread.h"
#include "os/UnixThreadContainer.h"

OS::UnixThreadContainer::UnixThreadContainer() {

}

void OS::UnixThreadContainer::task(const Callable::Task& task) {
    int dispatcherIndex = taskDispatcherCount % threadNumber;
    if (!threadNumber) {
        return;
    }
    threadDispatcherManager[dispatcherIndex]->addTask(task);
    taskDispatcherCount++;
}

void OS::UnixThreadContainer::start() {
    for(int i = 0; i < threadNumber; i++) {
        std::shared_ptr<UnixThread> thread = std::make_shared<UnixThread>();

        if (initClosure) {
            thread->setInitCallable(initClosure);
        }

        threadDispatcherManager.push_back(thread);

        //启动线程
        threadDispatcherManager[i]->Start();
    }
}

void OS::UnixThreadContainer::stop() {

}

OS::UnixThreadContainer::~UnixThreadContainer() {

}