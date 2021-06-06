//
// Created by zhanglei on 2021/5/20.
//

#include "skywalking/MarsSkyWalking.h"
#include "config/MarsConfig.h"
using namespace function;

skywalking::MarsSkyWalking::MarsSkyWalking(const std::shared_ptr<app::NodeAgent> &agent) {
    std::shared_ptr<config::MarsConfig>& marsConfig = agent->getMarsConfig();
    thread = std::make_shared<OS::UnixThread>();
    skywalkingConfig = std::make_shared<MarsSkyWalkingConfig>();
    try {
        skywalkingConfig->load(marsConfig->getYamlCore()[SKYWALKING_MODULE_NAME]);
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
    grpcHandle = std::make_shared<MarsSkyWalkingHandle>(skywalkingConfig, thread);
}

void skywalking::MarsSkyWalking::initFunction() {
    if (checkInit()) {
        return;
    }

    //注册skywalking
    if (!skywalkingConfig->getEnableReg()) {
        return;
    }

//
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

std::string skywalking::MarsSkyWalking::regSkyWalking(const std::string& serviceName, pid_t pid)
{
    if (!appRegString.empty()) {
        return appRegString;
    }

    mu.lock();
    if (!appRegString.empty()) {
        return appRegString;
    }
    bool res = grpcHandle->reg(serviceName);
    if (!res) {
        return "";
    }
    char pidStr[25];
    //这里使用sprintf
    sprintf(pidStr, "%u", pid);
    appRegString += (grpcHandle->getInstanceId() + ",");
    appRegString += (pidStr);
    appRegString += ("," + grpcHandle->getUuid());
    return appRegString;
}



void skywalking::MarsSkyWalking::shutdownFunction() {
    if (checkShutdown()) {
        return;
    }

    shutdownConfirm();
}