//
// Created by zhanglei on 2021/4/26.
//
extern "C" {
#include "evhttp.h"
}

#include "health/MarsHealthConfig.h"
#include "health/MarsProcessHealth.h"
#include "health/MarsHttpServerHealth.h"
#include "http/MarsHttpAction.h"

using namespace function::health;
using namespace std::placeholders;

/**
 * 一次性重载配置
 * @param node
 */
void MarsHealthConfig::load (const YAML::Node& node) {
    if (node["app"]) {
        app = node["app"].as<std::string>();
    }

    if (node["health_way"]) {
        health_way = node["health_way"].as<std::string>();
    }

    if (node["health_path"]) {
        health_path = node["health_path"].as<std::string>();
    }

    if (node["health_enable"]) {
        health_enable = node["health_enable"].as<bool>();
    }

    if (node["health_port"]) {
        health_port = node["health_port"].as<short>();
    }

    if (node["health_ip"]) {
        health_ip = node["health_ip"].as<std::string>();
    }

    if (node["http_path"]) {
        http_path = node["http_path"].as<std::string>();
    }
    action = std::make_shared<http::MarsHttpAction>();
    if (health_way == "http") {
        std::shared_ptr<MarsHttpServerHealth> server = std::make_shared<MarsHttpServerHealth>();
        action->setUsers(std::bind(&MarsHttpServerHealth::handle, server, _1));
    } else {
        std::shared_ptr<MarsProcessHealth> server = std::make_shared<MarsProcessHealth>();
        action->setUsers(std::bind(&MarsProcessHealth::handle, server, _1));
    }
}