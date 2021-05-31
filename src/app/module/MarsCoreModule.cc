//
// Created by zhanglei on 2021/4/26.
//
#include <memory>
#include "NodeAgent.h"
#include "module/MarsCoreModule.h"
#include "function/container/MarsFunctionContainer.h"
#include "function/http/MarsHttp.h"
#include "function/health/MarsHealth.h"
#include "promethean/MarsPromethean.h"
#include "skywalking/MarsSkyWalking.h"

using namespace module;
using namespace function;

MarsCoreModule::MarsCoreModule(const std::shared_ptr<app::NodeAgent> &agent) {
    nodeAgent = agent;
    container = std::make_shared<function::container::MarsFunctionContainer>();
}

void MarsCoreModule::loadApollo() {

}

void MarsCoreModule::loadEureka() {

}

void MarsCoreModule::loadHealth() {
    std::shared_ptr<health::MarsHealth> health = std::make_shared<health::MarsHealth>(nodeAgent);
    container->bind(healthModuleName, health);
}

void MarsCoreModule::loadHttp() {
    std::shared_ptr<function::http::MarsHttp> httpServer = std::make_shared<function::http::MarsHttp>(nodeAgent);
    container->bind(httpModuleName, httpServer);
}

void MarsCoreModule::loadOs() {

}

void MarsCoreModule::loadPromethean() {
    std::shared_ptr<function::promethean::MarsPromethean> prometheanServer = std::make_shared<function::promethean::MarsPromethean>(
            nodeAgent);
    container->bind(prometheanModuleName, prometheanServer);
}

void MarsCoreModule::loadWheel() {

}

//加载apollo
void MarsCoreModule::loadSkyWalking() {
    std::shared_ptr<function::skywalking::MarsSkyWalking> skyWalking = std::make_shared<function::skywalking::MarsSkyWalking>(
            nodeAgent);
    container->bind(prometheanModuleName, skyWalking);
}

void MarsCoreModule::loadJob() {

}

void MarsCoreModule::moduleInit() {
    loadSkyWalking();
    loadHttp();
    loadPromethean();
    loadApollo();
    loadEureka();
    loadHealth();
    loadOs();
    loadWheel();
    loadJob();

    auto moduleMap = container->getMap();
    auto moduleMapBegin = moduleMap.cbegin();
    auto moduleMapEnd = moduleMap.cend();

    for (; moduleMapBegin != moduleMapEnd; moduleMapBegin++) {
        moduleMapBegin->second->initFunction();
    }
}

void MarsCoreModule::moduleFinish() {
    auto moduleMap = container->getMap();
    auto moduleMapBegin = moduleMap.cbegin();
    auto moduleMapEnd = moduleMap.cend();

    for (; moduleMapBegin != moduleMapEnd; moduleMapBegin++) {
        moduleMapBegin->second->finishFunction();
    }
}

void MarsCoreModule::moduleDestroy() {
    auto moduleMap = container->getMap();
    auto moduleMapBegin = moduleMap.cbegin();
    auto moduleMapEnd = moduleMap.cend();

    for (; moduleMapBegin != moduleMapEnd; moduleMapBegin++) {
        moduleMapBegin->second->shutdownFunction();
        moduleMap.erase(moduleMapBegin);
    }
}

MarsCoreModule::~MarsCoreModule() {

}