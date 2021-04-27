//
// Created by zhanglei on 2021/4/19.
//

#ifndef MARS_AGENT_MARSCONFIG_H
#define MARS_AGENT_MARSCONFIG_H
#include "yaml-cpp/yaml.h"
#include <string>

namespace config {
    class MarsConfig {
    public:
        MarsConfig();

        //加载配置文件
        bool loadConfig(const std::string &configPath);

        ~MarsConfig();

        int getWorkerNumber() {
            return workerNumber;
        }

        bool getHealthEnable() {
            return healthEnable;
        }


        std::string getEnvName() {
            return envName;
        }

        std::string getApplicationName() {
            return marsApplicationName;
        }

        unsigned short getHttpPort() {
            return marsHttpPort;
        }

        std::string getHttpIp() {
            return marsHttpIp;
        }

        std::string getPidFile() {
            return pidFile;
        }

        int getHttpTimeout() {
            return marsHttpTimeout;
        }


    private:

        //生成worker的进程数目
        bool fillWorkerNumber();

        bool fillHealthEnable();

        bool fillPidFile();

        bool fillCore();

        bool fillEnv();

        bool fillApplicationName();

        bool fillHttpPort();

        bool fillHttpIp();

        bool fillHttpTimeOut();

        unsigned short workerNumber = 1;

        bool healthEnable = false;

        std::string envName = "prd";

        std::string marsApplicationName = "mars";

        unsigned short marsHttpPort = 11900;

        std::string marsHttpIp = "0.0.0.0";

        int marsHttpTimeout = 5;

        std::string pidFile;

        YAML::Node yamMars;

        YAML::Node yamlCore;

    };
}

#endif //MARS_AGENT_MARSCONFIG_H
