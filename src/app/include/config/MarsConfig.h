//
// Created by zhanglei on 2021/4/19.
//

#ifndef MARS_AGENT_MARSCONFIG_H
#define MARS_AGENT_MARSCONFIG_H

#include <string>

namespace YAML {
    class Node;
}
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

        unsigned short workerNumber = 1;

        bool healthEnable = false;

        std::string envName = "prd";

        std::string marsApplicationName = "mars";

        unsigned short marsHttpPort = 11900;

        std::string marsHttpIp = "0.0.0.0";

        int marsHttpTimeout = 5;

        std::string pidFile;



    };
}

#endif //MARS_AGENT_MARSCONFIG_H
