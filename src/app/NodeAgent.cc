//
// Created by zhanglei on 2021/3/6.
//


#include "NodeAgent.h"
#include "AgentWorker.h"
#include "NodeAgentCommand.h"
using namespace std::placeholders;

app::NodeAgent::NodeAgent() {
    //初始化命令行解析工具
    command = std::make_shared<NodeAgentCommand>();
    //初始化主线程的事件循环
    loop = std::make_shared<Event::EventLoop>();
    //初始化信号事件
    signalEvent = std::make_shared<Event::EventSignal>(loop);
    //初始化当前循环的信号处理
    loop->sigAdd(SIGTERM, dispatcherStopCommand, loop->getEventBase());
    signalEvent->bindEvent();
}

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
void app::NodeAgent::run(int argc, char** argv) {
    command->setCommandArgc(argc);
    command->setCommandArgv(argv);

    //解析命令
    command->dispatch();
    //开启工作的线程池
    std::shared_ptr<app::AgentWorker> worker = std::make_shared<AgentWorker>();
    //设置线程初始化函数
    Callable::initCallable initFunctionParam = std::bind(&NodeAgent::init, shared_from_this(), _1);
    //启动工作事件
    worker->Start();
    //开启线程池
    loop->loop();
}
