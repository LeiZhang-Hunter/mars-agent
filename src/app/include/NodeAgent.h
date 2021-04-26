//
// Created by zhanglei on 2021/3/6.
//

#ifndef UGC_NODE_AGENT_NODEAGENT_H
#define UGC_NODE_AGENT_NODEAGENT_H

#include <memory>
#include <csignal>
#include <vector>

#include "event/EventLoop.h"
#include "event/EventSignal.h"
#include "os/UnixCommand.h"

namespace function {
    template <class T> class MarsFunctionContainer;
    class MarsHttpServer;
}

/**
 * agent节点启动类
 */
namespace app {

    class NodeAgentCommand;
    class AgentWorker;

    typedef std::shared_ptr<function::MarsFunctionContainer<function::MarsHttpServer>> HttpContainerType;

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

        std::shared_ptr<Event::EventLoop> getLoop() {
            return loop;
        }

    private:
        std::shared_ptr<Event::EventLoop> loop;
        std::shared_ptr<Event::EventSignal> signalEvent;
        std::shared_ptr<NodeAgentCommand> command;
        HttpContainerType httpContainer;

        std::string httpCoreName = "httpKernel";
        std::vector<std::shared_ptr<app::AgentWorker>> workerPool;
    };
}

#endif //UGC_NODE_AGENT_NODEAGENT_H
