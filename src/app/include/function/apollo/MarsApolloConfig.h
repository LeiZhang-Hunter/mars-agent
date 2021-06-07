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
        struct apolloAppConfig {
            std::string appId;
            std::string cluster = "default";
            std::vector<std::pair<std::string, int>> localNamespaces = { {"application", -1} };
            std::string env = "dev";
        };
        class MarsApolloConfig {
        public:

            MarsApolloConfig() {

            }

            std::string& getServer() {
                return server;
            }

            std::vector<apolloAppConfig>& getAppConfig() {
                return appVector;
            }

            std::string& getApi() {
                return api;
            }

            std::string& getNotificationsUrl() {
                return notificationsUrl;
            }

            uint16_t getPort() {
                return port;
            }

            std::string& getStringPort() {
                return stringPort;
            }

            std::string getHost() {
                return host;
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
            std::string stringPort;
            std::string notificationsUrl =  "/notifications/v2";
            std::vector<apolloAppConfig> appVector;
            std::string host;
        };
    }
}

#endif //MARS_AGENT_MARSAPOLLOCONFIG_H
