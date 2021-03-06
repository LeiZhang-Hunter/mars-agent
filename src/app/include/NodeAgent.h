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

namespace OS {
    class UnixThreadContainer;
}

namespace config {
    class MarsConfig;
}

namespace module {
    class MarsCoreModule;
}

namespace function {
    class MarsFunctionObject;
    namespace container {
        class MarsFunctionContainer;
    }
    namespace http {
        class MarsHttp;
    }
}

/**
 * agent节点启动类
 */
namespace app {

    class NodeAgentCommand;

    class AgentWorker;


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

        std::shared_ptr<config::MarsConfig>& getMarsConfig() {
            return marsConfig;
        }

        /**
         * 停止
         */
        void stop();

        void test() {
            std::cout << "test" << std::endl;
        }

        /**
         * 运行
         */
        void run(int argc, char **argv);

        std::shared_ptr<Event::EventLoop> getLoop() {
            return loop;
        }

        std::shared_ptr<module::MarsCoreModule> getCoreModule() {
            return coreModule;
        }

        std::shared_ptr<OS::UnixThreadContainer> getUnixThreadContainer() {
            return threadContainer;
        }

    private:
        std::shared_ptr<Event::EventLoop> loop;
        std::shared_ptr<Event::EventSignal> signalEvent;
        std::shared_ptr<NodeAgentCommand> command;
        std::shared_ptr<config::MarsConfig> marsConfig;
        std::shared_ptr<module::MarsCoreModule> coreModule;
        std::shared_ptr<OS::UnixThreadContainer> threadContainer;
    };
}

#endif //UGC_NODE_AGENT_NODEAGENT_H
