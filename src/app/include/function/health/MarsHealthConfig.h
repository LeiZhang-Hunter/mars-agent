//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSHEALTHCONFIG_H
#define MARS_AGENT_MARSHEALTHCONFIG_H

#include "yaml-cpp/yaml.h"
#include <string>
#include <functional>
namespace function {
    namespace http {
        class MarsHttpAction;
    }
    namespace health {
        class MarsHealthConfig {
        public:
            std::string app;
            std::string health_way = "pid_file";
            std::string health_path;
            bool health_enable = false;
            short health_port = 9000;
            std::string health_ip = "0.0.0.0";
            std::string http_path = "/health";

            //处理句柄
            std::shared_ptr<http::MarsHttpAction> action;

            void load (const YAML::Node& node);
        };
    }
}
#endif //MARS_AGENT_MARSHEALTHCONFIG_H
