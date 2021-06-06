//
// Created by zhanglei on 2021/6/6.
//

#ifndef MARS_AGENT_MARSAPOLLOCLIENT_H
#define MARS_AGENT_MARSAPOLLOCLIENT_H

#include "MarsApolloConfig.h"
#include "MarsApolloApi.h"

namespace function {
    namespace apollo {
        class MarsApolloClient {
        public:
            MarsApolloClient(const std::shared_ptr<MarsApolloConfig> &config_) : config(config_) {
                apolloApi = std::make_shared<MarsApolloApi>();
            }

            void run();

        private:
            std::vector<std::pair<std::string, int>>& initLocalNamespaces();
            static void onNotifications(struct evhttp_request *req, void *arg);
            const std::shared_ptr<MarsApolloConfig> &config;
            std::shared_ptr<MarsApolloApi> apolloApi;
            std::vector<std::pair<std::string, int>> localNamespaces;
        };
    }
}

#endif //MARS_AGENT_MARSAPOLLOCLIENT_H
