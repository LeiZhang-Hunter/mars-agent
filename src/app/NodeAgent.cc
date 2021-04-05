//
// Created by zhanglei on 2021/3/6.
//


#include "NodeAgent.h"

void app::NodeAgent::dispatcherStopCommand(evutil_socket_t sig, short events, void *param) {
    std::cout << "dispatcherStopCommand" << std::endl;
    auto agent = static_cast<NodeAgent *>(param);
    agent->stop();
}

void app::NodeAgent::stop() {
    std::cout << "stop" << std::endl;
    loop->quit();
}

/**
 * 坚持 one thread loop 模型，主线程负责接收信号，接收请求
 * 子线程负责处理逻辑
 * 子线程负责具体的工作
 */
void app::NodeAgent::run() {
    //添加信号处理器
    std::cout << signalEvent.use_count() << std::endl;
    signalEvent->setSignal(SIGTERM, dispatcherStopCommand, this);
    signalEvent->bindEvent();
    loop->loop();
}
