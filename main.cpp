#include <iostream>
#include <jemalloc/jemalloc.h>
#include <memory>

#include "NodeAgent.h"

int main(int argc, char** argv) {
    //初始化agent
    std::shared_ptr<app::NodeAgent> agent = std::make_shared<app::NodeAgent>();
    agent->setCommandArgc(argc);
    agent->setCommandArgv(argv);
    //启动整个agent
    agent->run();
    return 0;
}
