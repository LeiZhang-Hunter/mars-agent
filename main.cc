#include <iostream>
#include <jemalloc/jemalloc.h>
#include <memory>

#include "NodeAgent.h"

int main(int argc, char** argv) {
    signal(SIGPIPE, SIG_IGN);
    //初始化agent
    std::shared_ptr<app::NodeAgent> agent = std::make_shared<app::NodeAgent>();
    //启动整个agent
    agent->run(argc, argv);
    return 0;
}
