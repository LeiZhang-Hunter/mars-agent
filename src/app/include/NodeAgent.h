//
// Created by zhanglei on 2021/3/6.
//

#ifndef UGC_NODE_AGENT_NODEAGENT_H
#define UGC_NODE_AGENT_NODEAGENT_H

#include <memory>
#include <csignal>

#include "event/EventLoop.h"
#include "event/EventSignal.h"
#include "os/UnixCommand.h"

/**
 * agent节点启动类
 */
namespace app {

    class NodeAgentCommand;

    class NodeAgent : public std::enable_shared_from_this<NodeAgent> {

    public:
        /**
         * 初始化工具
         */
        NodeAgent();


        static void dispatcherStopCommand(int fd, short events, void *arg);

        /**
         * 初始化配置
         */
        void init(const std::shared_ptr<Event::EventLoop> &threadLoop);

        /**
         * 停止
         */
        void stop();

        /**
         * 运行
         */
        void run(int argc, char **argv);

    private:
        std::shared_ptr<Event::EventLoop> loop;
        std::shared_ptr<Event::EventSignal> signalEvent;
        std::shared_ptr<NodeAgentCommand> command;
    };
}

#endif //UGC_NODE_AGENT_NODEAGENT_H
