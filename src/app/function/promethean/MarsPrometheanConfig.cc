//
// Created by zhanglei on 2021/4/16.
//
#include <string>
#include <iostream>


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

    try {
        clientMaxBuffer = node["unix_client_max_buffer"].as<uint64_t>();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    try {
        idleTime = node["wheel_idle_time"].as<uint64_t>();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    try {
        checkInterval = node["wheel_check_interval"].as<uint64_t>();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    try {
        maxConnection = node["max_connection"].as<uint64_t>();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}