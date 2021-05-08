//
// Created by zhanglei on 2021/4/16.
//
#include <string>

#include "yaml-cpp/yaml.h"

#include "promethean/MarsPrometheanConfig.h"
using namespace function::promethean;
/**
 * 一次性重载配置
 * @param node
 */
void MarsPrometheanConfig::load(const YAML::Node &node) {
    if (node["unix_path"]) {
        unix_path = node["unix_path"].as<std::string>();
    }

    if (node["http_path"]) {
        http_path = node["http_path"].as<std::string>();
    }


}