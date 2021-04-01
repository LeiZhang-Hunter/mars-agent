//
// Created by zhanglei on 2021/3/6.
//

#ifndef UGC_NODE_AGENT_NODEAGENT_H
#define UGC_NODE_AGENT_NODEAGENT_H

#include <memory>

#include "os/UnixCommand.h"

/**
 * agent节点启动类
 */
namespace app {
    class NodeAgent {

    public:
        /**
         * 初始化工具
         */
        NodeAgent() {
            //初始化命令行解析工具
            command = std::make_shared<OS::UnixCommand>();
        }

        /**
         * 设置argc 参数
         * @param argc
         * @return
         */
        bool setCommandArgc(int argc) {
            command->setCmdArgC(argc);
            return true;
        }

        /**
         * 设置argv参数
         * @param argv
         * @return
         */
        bool setCommandArgv(char **argv) {
            command->setCmdArgV(argv);
            return true;
        }

        void run();

    private:
        std::shared_ptr<OS::UnixCommand> command;
    };
}

#endif //UGC_NODE_AGENT_NODEAGENT_H
