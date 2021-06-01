//
// Created by zhanglei on 2021/5/20.
//

#include "skywalking/MarsSkyWalking.h"
#include "config/MarsConfig.h"
using namespace function;

skywalking::MarsSkyWalking::MarsSkyWalking(const std::shared_ptr<app::NodeAgent> &agent) {
    std::shared_ptr<config::MarsConfig> marsConfig = agent->getMarsConfig();
    thread = std::make_shared<OS::UnixThread>();
    skywalkingConfig = std::make_shared<MarsSkyWalkingConfig>();
    try {
        skywalkingConfig->load(marsConfig->getYamlCore()[SKYWALKING_MODULE_NAME]);
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
    grpcHandle = std::make_shared<MarsSkyWalkingHandle>(skywalkingConfig);
}

void skywalking::MarsSkyWalking::initFunction() {
    if (checkInit()) {
        return;
    }

    //注册skywalking

    //启动一个grpc线程，因为grpc是同步的
    thread->Start();
    initConfirm();
}

void skywalking::MarsSkyWalking::finishFunction() {
    if (checkFinish()) {
        return;
    }

    finishConfirm();
}

std::string skywalking::MarsSkyWalking::regSkyWalking()
{
//    thread->addTask();
    return "";
}



void skywalking::MarsSkyWalking::shutdownFunction() {
    if (checkShutdown()) {
        return;
    }

    shutdownConfirm();
}