//
// Created by zhanglei on 2020/11/12.
//

#include <sys/eventfd.h>

#include "os/UnixCurrentThread.h"
#include "event/EventQueue.h"
#include "event/EventLoop.h"
#include "os/UnixThread.h"
#include "event/Channel.h"

OS::UnixThread::UnixThread() {
    //初始化互斥锁
    mTerminated = false;
    daemonize = false;
    isSuspend = false;
    mRunStatus = false;
    loop = std::make_shared<Event::EventLoop>();
    latch = std::make_shared<UnixCountDownLatch>(1);
    //创建独立的线程运行空间
    proc = new UnixThreadProc(loop, latch);
    //创建管道的fd
    wakeupChannelFd = createChannelFd();
}

int OS::UnixThread::createChannelFd() {
    return eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
}

/**
 * 析构函数如果对象不是守护线程需要用join进行释放
 */
OS::UnixThread::~UnixThread() {

    if (daemonize) {
        goto release;
    }

    void *status;
    if (mRunStatus && pthread_join(mThreadID, &status) != 0) {
        std::cerr << "CThread->ReleaseThread Join Error" << std::endl;
    }

    //释放申请的内存
    release:
    //删除线程处理的栈内存
    delete proc;
}

/**
 * 线程运行的主程序
 * @param arg
 * @return
 */
void *OS::UnixThread::ThreadProc(void *arg) {

    //创建独立的线程运行空间
    auto *proc = static_cast<OS::UnixThreadProc *>(arg);

    //运行线程
    proc->runThread();

    return (void *) nullptr;
}

//启动线程
bool OS::UnixThread::Start() {
    //队列
    queue = std::make_shared<Event::EventQueue>(shared_from_this());
    if (wakeupChannelFd != -1) {
        channel = std::make_shared<Event::Channel>(loop, wakeupChannelFd);
        channel->setEvents(EV_PERSIST);
        channel->setOnReadCallable((std::bind(&UnixThread::OnTask, shared_from_this())));
        //开启读取事件
        channel->enableReading(-1);
    }

    /*
     * 初始化一个锁属性
     */
    pthread_attr_init(&attr);

    mRunStatus = false;


    /*
     *启动线程
     */
    if (pthread_create(&mThreadID, &attr, ThreadProc, proc) == 0) {
        mRunStatus = true;
    } else {
        delete proc;
        return mRunStatus;
    }

    //等待所有线程初始化完成工作
    latch->wait();

    //创建线程之间通讯的channel

    tid = proc->getThreadTid();
    /*
     *释放属性
     */
    pthread_attr_destroy(&attr);
    return mRunStatus;
}

void OS::UnixThread::OnTask() {
    queue->dispatchTask();
}

ssize_t OS::UnixThread::wakeUp() {
    uint64_t notify = 1;
    ssize_t n = ::write(wakeupChannelFd, &notify, sizeof(notify));
    if (n != sizeof(notify)) {
        std::cerr << "thread " << getTid() << " wake up " << wakeupChannelFd << " failed !" << std::endl;
    }
}

void OS::UnixThread::addTask(const Callable::Task &task) {
    queue->pushTask(task);
}

