//
// Created by zhanglei on 2021/5/30.
//

#ifndef MARS_AGENT_MARSSKYWALKINGCONFIG_H
#define MARS_AGENT_MARSSKYWALKINGCONFIG_H
#include <string>
#include <iostream>

#include "yaml-cpp/yaml.h"

namespace function {
    namespace skywalking {
        class MarsSkyWalkingConfig {
        public:
            MarsSkyWalkingConfig() {

            }

            ~MarsSkyWalkingConfig() {

            }
            //加载配置
            void load (const YAML::Node& node);

            std::string getGrpcAddress()
            {
                return grpcAddress;
            }

            bool getEnableReg()
            {
                return enable_reg;
            }

            size_t getHeartbeatTime()
            {
                return heartbeat_time;
            }

        private:
            std::string grpcAddress = "";

            //是否启用注册
            bool enable_reg = false;

            //心跳时间
            size_t heartbeat_time = 0;
        };
    }
}

#endif //MARS_AGENT_MARSSKYWALKINGCONFIG_H
