//
// Created by zhanglei on 2021/4/26.
//
#include "container/MarsFunctionContainer.h"

using namespace function::container;

bool MarsFunctionContainer::init(const std::shared_ptr<config::MarsConfig> &marsConfig) {

    return true;
}

bool MarsFunctionContainer::bind(const std::string &id,
        const std::shared_ptr<function::MarsFunctionObject> &server) {
    if (id.empty()) {
        return false;
    }
    auto instance = containerMap.find(id);
    return !(instance != containerMap.end());
}

bool MarsFunctionContainer::has(const std::string &id) {

    if (id.empty()) {
        return false;
    }

    auto instance = containerMap.find(id);
    return instance != containerMap.end();
}

std::shared_ptr<function::MarsFunctionObject> MarsFunctionContainer::get(const std::string &id) {

    if (id.empty()) {
        return std::shared_ptr<function::MarsFunctionObject>();
    }

    auto instance = containerMap.find(id);
    if (instance != containerMap.end()) {
        return std::shared_ptr<function::MarsFunctionObject>();
    }

    return instance->second;
}