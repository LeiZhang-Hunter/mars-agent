//
// Created by zhanglei on 2021/6/6.
//

#ifndef MARS_AGENT_MARSAPOLLOCONFIG_H
#define MARS_AGENT_MARSAPOLLOCONFIG_H

#include <memory>
#include <yaml-cpp/yaml.h>
#include <string>

#include "MarsFunctionObject.h"

namespace function {
    namespace apollo {
        class MarsApolloConfig {
        public:
            MarsApolloConfig() {

            }

            /**
             * 加载配置
             * @param node
             */
            void load (const YAML::Node& node);

        private:
            std::string api;
            std::string server;
            uint16_t port;
            struct apolloAppConfig {
                std::string appId;
                std::string cluster = "default";
                std::vector<std::string> localNamespaces = {"application"};
                std::string env = "dev";
            };
            std::vector<apolloAppConfig> appVector;
        };
    }
}

#endif //MARS_AGENT_MARSAPOLLOCONFIG_H
