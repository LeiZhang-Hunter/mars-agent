//
// Created by zhanglei on 2021/4/19.
//

extern "C" {
#include <unistd.h>
#include <fcntl.h>
}

#include <climits>
#include <memory>
#include <cstring>
#include <csignal>

#include "config/MarsConfig.h"
#include "os/UnixCommand.h"
#include "os/UnixPidFile.h"
#include "NodeAgentCommand.h"

using namespace std::placeholders;

app::NodeAgentCommand::NodeAgentCommand() {
    command = std::make_shared<OS::UnixCommand>();
    config = std::make_shared<config::MarsConfig>();
    pidFileObject = std::make_shared<OS::UnixPidFile>();
}

bool app::NodeAgentCommand::getConfigPath(int argc, char **argv, const char &value) {
    configFile = argv[optind];
    return true;
}

bool app::NodeAgentCommand::serviceOperate(int argc, char **argv, const char &value) {
    operation = argv[optind];
    return true;
}

bool app::NodeAgentCommand::dispatch() {
    //加载配置文件
    command->reg('c', std::bind(&NodeAgentCommand::getConfigPath, shared_from_this(), _1, _2, _3));
    //执行程序
    command->reg('e', std::bind(&NodeAgentCommand::serviceOperate, shared_from_this(), _1, _2, _3));
    //解析命令
    command->parse();

    //校验配置文件输入的合理性
    if (configFile.empty()) {
        std::cerr << "The configuration file cannot be empty" << std::endl;
        exit(-1);
    }

    //转换为绝对路径
    char dir[PATH_MAX];
    realpath(configFile.c_str(), dir);
    int ret = access(dir, F_OK);
    if (ret == -1) {
        std::cerr << "The configuration file(" << dir << ") error: " << strerror(errno) << std::endl;
        exit(-1);
    }

    //加载yaml
    bool loadRet = config->loadConfig(configFile);
    if (!loadRet) {
        std::cerr << "The configuration load error!" << std::endl;
        exit(-1);
    }

    //获取配置文件路径
    std::string pidFile = config->getPidFile();
    if (pidFile.empty()) {
        std::cerr << "mars[pid_file] not empty!" << std::endl;
        exit(-1);
    }

    pidFileObject->open(pidFile, O_RDONLY | O_WRONLY | O_CREAT);

    //查看这个文件是否加锁了
    if (operation == "stop") {
        pid_t pid = pidFileObject->getPid();

        if (pid <= 0) {
            std::cerr << "get pid error!" << std::endl;
            exit(-1);
        }

        int res = kill(pid, SIGTERM);
        if (res == -1) {
            std::cerr << strerror(errno) << std::endl;
            exit(-1);
        }
        exit(0);

    }

    if (!pidFileObject->tryWriteLock()) {
        std::cerr << "process has been start" << std::endl;
        exit(-1);
    }

    pidFileObject->setPid();
    return true;
}

app::NodeAgentCommand::~NodeAgentCommand() {
    command.reset();
}