//
// Created by zhanglei on 2021/4/26.
//
#include <memory>
#include "NodeAgent.h"
#include "module/MarsCoreModule.h"
#include "function/container/MarsFunctionContainer.h"
#include "function/http/MarsHttp.h"
#include "function/health/MarsHealth.h"

using namespace module;
using namespace function;

MarsCoreModule::MarsCoreModule(const std::shared_ptr<app::NodeAgent>& agent) {
    container = std::make_shared<function::container::MarsFunctionContainer>();
    loadApollo();
    loadEureka();
    loadHealth();
    loadHttp();
    loadOs();
    loadPromethean();
    loadWheel();
    loadJob();
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

}

void MarsCoreModule::loadWheel() {

}

void MarsCoreModule::loadJob() {

}

void MarsCoreModule::moduleInit() {
    auto moduleMap = container->getMap();
    auto moduleMapBegin = moduleMap.cbegin();
    auto moduleMapEnd = moduleMap.cend();

    for(; moduleMapBegin != moduleMapEnd; moduleMapBegin++) {
        moduleMapBegin->second->initFunction();
    }
}

void MarsCoreModule::moduleDestroy() {
    auto moduleMap = container->getMap();
    auto moduleMapBegin = moduleMap.cbegin();
    auto moduleMapEnd = moduleMap.cend();

    for(; moduleMapBegin != moduleMapEnd; moduleMapBegin++) {
        moduleMapBegin->second->shutdownFunction();
        moduleMap.erase(moduleMapBegin);
    }
}

MarsCoreModule::~MarsCoreModule() {

}