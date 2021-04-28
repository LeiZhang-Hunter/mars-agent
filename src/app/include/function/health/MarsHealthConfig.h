//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSHEALTHCONFIG_H
#define MARS_AGENT_MARSHEALTHCONFIG_H

#include "yaml-cpp/yaml.h"
#include <string>

namespace function {
    namespace health {
        class MarsHealthConfig {
        public:
            std::string app;
            std::string health_way;
            std::string health_path;
            bool health_enable = false;
            short health_port = 9000;
            std::string health_ip = "0.0.0.0";

            /**
             * 一次性重载配置
             * @param node
             */
            void load (const YAML::Node& node) {
                if (node["app"]) {
                    app = node["app"].as<std::string>();
                }

                if (node["health_way"]) {
                    health_way = node["health_way"].as<std::string>();
                }

                if (node["health_path"]) {
                    health_path = node["health_path"].as<std::string>();
                }

                if (node["health_enable"]) {
                    health_enable = node["health_enable"].as<bool>();
                }

                if (node["health_port"]) {
                    health_port = node["health_port"].as<short>();
                }

                if (node["health_ip"]) {
                    health_ip = node["health_ip"].as<std::string>();
                }
            }
        };
    }
}
#endif //MARS_AGENT_MARSHEALTHCONFIG_H
