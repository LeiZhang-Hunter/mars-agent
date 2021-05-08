//
// Created by zhanglei on 2021/5/8.
//

#include "promethean/MarsPromethean.h"
#include "NodeAgent.h"
#include "config/MarsConfig.h"
#include "function/http/MarsHttpAction.h"
#include "module/MarsCoreModule.h"
#include "http/MarsHttp.h"
#include "http/MarsHttpRouter.h"
#include "promethean/MarsPrometheanConfig.h"
using namespace function;
promethean::MarsPromethean::MarsPromethean(const std::shared_ptr<app::NodeAgent> &agent) {
    std::shared_ptr<config::MarsConfig> marsConfig = agent->getMarsConfig();
    if (!agent) {
        return;
    }
    router = agent->getCoreModule()->getObject<http::MarsHttp>(HTTP_MODULE_NAME)->getRouter();
    prometheanConfig = std::make_shared<MarsPrometheanConfig>();
    //加载配置
    auto yamPromethean = marsConfig->getYamlCore()[PROMETHEAN_MODULE_NAME];
    if (yamPromethean) {
        prometheanConfig->load(yamPromethean);
    }
}

void promethean::MarsPromethean::initFunction() {

}

void promethean::MarsPromethean::shutdownFunction() {
}

promethean::MarsPromethean::~MarsPromethean() {

}