//
// Created by zhanglei on 2021/4/26.
//
#include "NodeAgent.h"
#include "function/health/MarsHealth.h"
#include "function/http/MarsHttp.h"
#include "function/http/MarsHttpRouter.h"
#include "config/MarsConfig.h"
#include "module/MarsCoreModule.h"
#include "function/http/MarsHttpAction.h"
#include "function/health/MarsHealthConfig.h"
#include "function/health/MarsHttpServerHealth.h"
#include "function/health/MarsProcessHealth.h"

using namespace function::health;

MarsHealth::MarsHealth(const std::shared_ptr<app::NodeAgent> &agent) {
    if (!agent) {
        return;
    }
    router = agent->getCoreModule()->getObject<http::MarsHttp>(HTTP_MODULE_NAME)->getRouter();
    //加载配置
    std::shared_ptr<config::MarsConfig>& marsConfig = agent->getMarsConfig();
    loadConfig(marsConfig->getYamlCore());
}

void MarsHealth::initFunction() {
    if (isInit) {
        return;
    }
    //循环配置文件
    for (auto it = healthConfig.begin(); it != healthConfig.end(); it++) {
        router->getRequest(it->second->http_path, it->second->action);
    }
    isInit = true;
}

void MarsHealth::shutdownFunction() {
    if (!isInit) {
        return;
    }
    isInit = false;
}

bool MarsHealth::loadConfig(const YAML::Node& yamlConfig) {
    auto& yamlHealth = yamlConfig[HEALTH_MODULE_NAME];
    if (!yamlHealth) {
        return false;
    }

    for(unsigned i=0; i < yamlHealth.size(); i++) {
        auto yamlAppName = yamlHealth[i]["app"];
        if (!yamlAppName)
            continue;

        std::string healthAppName = yamlAppName.as<std::string>();
        std::shared_ptr<MarsHealthConfig> config = std::make_shared<MarsHealthConfig>();
        config->load(yamlHealth[i]);
        healthConfig[healthAppName] = config;
    }
    return true;
}

MarsHealth::~MarsHealth() {

}