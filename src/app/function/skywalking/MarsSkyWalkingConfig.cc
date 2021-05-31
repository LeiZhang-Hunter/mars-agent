//
// Created by zhanglei on 2021/5/30.
//
#include "skywalking/MarsSkyWalkingConfig.h"

using namespace function;

void skywalking::MarsSkyWalkingConfig::load(const YAML::Node &node) {
    try {
        grpcAddress = node["grpc"].as<std::string>();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    try {
        enable_reg = node["enable_reg"].as<bool>();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    try {
        heartbeat_time = node["heartbeat_time"].as<uint64_t>();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}