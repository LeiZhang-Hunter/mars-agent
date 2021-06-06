//
// Created by zhanglei on 2021/4/16.
//

#ifndef MARS_AGENT_MARSPROMETHEANCONFIG_H
#define MARS_AGENT_MARSPROMETHEANCONFIG_H
#include "yaml-cpp/yaml.h"

namespace function {
    namespace http {
        class MarsHttpAction;
    }
    namespace promethean {
        class MarsPrometheanConfig {
        public:
            std::string unix_path;
            std::string http_path = "/metrics";



            //处理句柄
            std::shared_ptr<http::MarsHttpAction> action;

            void load (const YAML::Node& node);

            size_t getClientBufferSize() {
                return clientMaxBuffer;
            }

            size_t getIdleTime() {
                return idleTime;
            }

            size_t getCheckInterval() {
                return checkInterval;
            }

            long getMaxConnection() {
                return maxConnection;
            };

        private:
            //客户端缓冲区的最大长度
            size_t clientMaxBuffer = 65535;

            //时间轮的检查时间
            size_t idleTime = 480;

            //轮盘的大小
            size_t checkInterval = 60;

            long maxConnection = 600;
        };
    }
}
#endif //MARS_AGENT_MARSPROMETHEANCONFIG_H
