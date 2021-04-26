//
// Created by zhanglei on 2021/4/20.
//
#include <string>

#include "config/MarsConfig.h"

config::MarsConfig::MarsConfig() {

}

bool config::MarsConfig::loadConfig(const std::string &configPath) {
    YAML::Node marsYamConfig = YAML::LoadFile(configPath);

    yamMars = marsYamConfig["mars"];
    if (!yamMars) {
        return false;
    }

    //生成各种配置选项
    fillWorkerNumber();
    fillHealthEnable();
    fillPidFile();
    fillCore();
    fillEnv();
    fillApplicationName();
    fillHttpPort();
    fillHttpIp();
    fillHttpTimeOut();
    return true;
}

bool config::MarsConfig::fillHttpPort() {
    auto yamlHttpPort = yamlCore["http_port"];
    if (yamlHttpPort) {
        marsHttpPort = yamlHttpPort.as<unsigned short>();
    }
    return true;
}

bool config::MarsConfig::fillHttpIp() {
    auto yamlHttpIp = yamlCore["http_ip"];
    if (yamlHttpIp) {
        marsHttpIp = yamlHttpIp.as<std::string>();
    }
    return true;
}

bool config::MarsConfig::fillHttpTimeOut() {
    auto yamlHttpTimeout = yamlCore["http_timeout"];
    if (yamlHttpTimeout) {
        marsHttpTimeout = yamlHttpTimeout.as<int>();
    }
    return true;
}

bool config::MarsConfig::fillWorkerNumber() {
    //解析worker的数量
    auto yamlWorkerNumber = yamMars["worker_number"];
    if (yamlWorkerNumber) {
        workerNumber = yamlWorkerNumber.as<unsigned short>();
    }
    return true;
}

bool config::MarsConfig::fillHealthEnable() {
    auto yamlHealthEnable = yamMars["health_enable"];
    if (yamlHealthEnable) {
        healthEnable = yamlHealthEnable.as<bool>();
    }
    return true;
}

bool config::MarsConfig::fillPidFile() {
    auto yamlPidFile = yamMars["pid_file"];
    if (!yamlPidFile) {
        throw std::logic_error("yaml config pid_file error!");
        return false;
    }
    pidFile = yamlPidFile.as<std::string>();
    return true;
}

bool config::MarsConfig::fillCore() {
    yamlCore = yamMars["core"];
    return !!yamlCore;
}

bool config::MarsConfig::fillEnv() {
    auto yamlEnv = yamlCore["env"];
    if (yamlEnv) {
        envName = yamlEnv.as<std::string>();
    } else {
        envName = getenv("ENV_NAME");
    }
    return true;
}

bool config::MarsConfig::fillApplicationName() {
    //服务的名字
    auto yamlApplicationName = yamlCore["name"];
    if (yamlApplicationName) {
        marsApplicationName = yamlApplicationName.as<std::string>();
    }
    return true;
}

config::MarsConfig::~MarsConfig() {

}
