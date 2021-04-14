//
// Created by zhanglei on 2021/3/6.
//


#include "NodeAgent.h"
#include "AgentWorker.h"
using namespace std::placeholders;
void app::NodeAgent::dispatcherStopCommand(evutil_socket_t sig, short events, void *param) {
    std::cout << "dispatcherStopCommand" << std::endl;
    auto agent = static_cast<NodeAgent *>(param);
    agent->stop();
}

void app::NodeAgent::stop() {
    std::cout << "stop" << std::endl;
    loop->quit();
}

void app::NodeAgent::init(const std::shared_ptr<Event::EventLoop>& threadLoop) {
    threadLoop->sigAdd(SIGTERM, dispatcherStopCommand, threadLoop->getEventBase());
    signalEvent->bindEvent();
}

/**
 * 坚持 one thread loop 模型，主线程负责接收信号，接收请求
 * 子线程负责处理逻辑
 * 子线程负责具体的工作
 */
void app::NodeAgent::run() {
    //添加信号处理器
//    std::cout << signalEvent.use_count() << std::endl;
//    signalEvent->setSignal(SIGTERM, dispatcherStopCommand, this);
//    signalEvent->bindEvent();

    //初始化当前循环的信号处理
    init(loop);
    //开启工作的线程池
    std::shared_ptr<app::AgentWorker> worker = std::make_shared<AgentWorker>();
    //设置线程初始化函数
    Callable::initCallable initFunctionParam = std::bind(&NodeAgent::init, shared_from_this(), _1);
    worker->Start();
    std::cout << "thread" << std::endl;
    //开启线程池
    loop->loop();
}
