//
// Created by zhanglei on 2021/4/19.
//
#include <memory>
#include "os/UnixCommand.h"
#include "NodeAgentCommand.h"

using namespace std::placeholders;

app::NodeAgentCommand::NodeAgentCommand() {
    command = std::make_shared<OS::UnixCommand>();
}

bool app::NodeAgentCommand::getConfigPath(int argc, char **argv, const char &value) {
    return true;
}

bool app::NodeAgentCommand::serviceOperate(int argc, char **argv, const char &value) {
    return true;
}

bool app::NodeAgentCommand::dispatch() {
    //加载配置文件
    command->reg('c', std::bind(&NodeAgentCommand::getConfigPath, shared_from_this(), _1, _2, _3));
    //执行程序
    command->reg('e', std::bind(&NodeAgentCommand::serviceOperate, shared_from_this(), _1, _2, _3));
    //解析命令
    command->parse();
}

app::NodeAgentCommand::~NodeAgentCommand() {
    command.reset();
}