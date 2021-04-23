//
// Created by zhanglei on 2021/4/20.
//
#include <string>
#include "yaml-cpp/yaml.h"

#include "config/MarsConfig.h"

config::MarsConfig::MarsConfig() {

}

bool config::MarsConfig::loadConfig(const std::string &configPath) {
    YAML::Node marsYamConfig = YAML::LoadFile(configPath);

    if (!marsYamConfig["mars"]) {
        return false;
    }

    //解析worker的数量
    auto yamlWorkerNumber = marsYamConfig["mars"]["worker_number"];
    if (yamlWorkerNumber) {
        workerNumber = yamlWorkerNumber.as<unsigned short>();
    }
    auto yamlHealthEnable = marsYamConfig["mars"]["health_enable"];
    if (yamlHealthEnable) {
        healthEnable = yamlHealthEnable.as<bool>();
    }

    auto yamlPidFile = marsYamConfig["mars"]["pid_file"];
    if (!yamlPidFile) {
        return false;
    }
    pidFile = yamlPidFile.as<std::string>();

    auto yamlCore = marsYamConfig["mars"]["core"];
    if (!yamlCore) {
        return false;
    }

    auto yamlEnv = yamlCore["env"];
    if (yamlEnv) {
        envName = yamlEnv.as<std::string>();
    } else {
        envName = getenv("ENV_NAME");
    }

    //服务的名字
    auto yamlApplicationName = yamlCore["name"];
    if (yamlEnv) {
        marsApplicationName = yamlApplicationName.as<std::string>();
    }

    auto yamlHttpPort = yamlCore["http_port"];
    if (yamlHttpPort) {
        marsHttpPort = yamlHttpPort.as<unsigned short>();
    }

    auto yamlHttpIp = yamlCore["http_ip"];
    if (yamlHttpIp) {
        marsHttpIp = yamlHttpIp.as<std::string>();
    }

    return true;
}

config::MarsConfig::~MarsConfig() {

}
