//
// Created by zhanglei on 2021/4/19.
//

#ifndef MARS_AGENT_NODEAGENTCOMMAND_H
#define MARS_AGENT_NODEAGENTCOMMAND_H

#include <memory>
#include "Noncopyable.h"

namespace OS {
    class UnixCommand;
}

namespace app {
    class NodeAgentCommand
            : public Noncopyable, public std::enable_shared_from_this<NodeAgentCommand> {

    public:
        NodeAgentCommand();

        ~NodeAgentCommand();

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

        std::shared_ptr<OS::UnixCommand> getCommand() {
            return command;
        }

        bool dispatch();

    private:

        //获取配置文件地址
        bool getConfigPath(int argc, char **argv, const char &value);

        //执行操作
        bool serviceOperate(int argc, char **argv, const char &value);

        //命令行解析器
        std::shared_ptr<OS::UnixCommand> command;


    };
}

#endif //MARS_AGENT_NODEAGENTCOMMAND_H
