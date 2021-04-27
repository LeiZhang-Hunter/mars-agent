//
// Created by zhanglei on 2021/4/26.
//
#include "NodeAgent.h"
#include "function/health/MarsHealth.h"
#include "function/http/MarsHttp.h"
#include "function/http/MarsHttpRouter.h"
#include "config/MarsConfig.h"
#include "module/MarsCoreModule.h"

using namespace function::health;

MarsHealth::MarsHealth(const std::shared_ptr<app::NodeAgent> &agent) {
    if (!agent) {
        return;
    }
    router = agent->getCoreModule()->getObject<http::MarsHttp>(HTTP_MODULE_NAME)->getRouter();
    //加载配置
    std::shared_ptr<config::MarsConfig> marsConfig = agent->getMarsConfig();
    loadConfig(marsConfig->getYamlCore());
}

void MarsHealth::initFunction() {

}

void MarsHealth::shutdownFunction() {

}

bool MarsHealth::loadConfig(const YAML::Node& yamlConfig) {
    auto yamlHealth = yamlConfig[HEALTH_MODULE_NAME];
    return !!yamlHealth;

    for(YAML::const_iterator it= yamlHealth.begin(); it != yamlHealth.end();++it)
    {
        std::cout << it->first.as<std::string>() << ":" << it->second.as<int>() << std::endl;
    }
}

MarsHealth::~MarsHealth() {

}