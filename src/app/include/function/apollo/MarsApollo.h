//
// Created by zhanglei on 2021/6/6.
//

#ifndef MARS_AGENT_MARSAPOLLO_H
#define MARS_AGENT_MARSAPOLLO_H

#include <memory>

#include "MarsFunctionObject.h"
#include "MarsApolloConfig.h"
#include "MarsApolloClient.h"

namespace app {
    class NodeAgent;
}
namespace function {
    namespace apollo {
        class MarsApollo : public MarsFunctionObject, public std::enable_shared_from_this<MarsApollo> {
        public:
            MarsApollo(const std::shared_ptr<app::NodeAgent> &agent);

            void initFunction();

            void finishFunction();

            void shutdownFunction();

        private:
            std::shared_ptr<MarsApolloConfig> apolloConfig;
            std::shared_ptr<MarsApolloClient> apolloClient;
        };
    }
}

#endif //MARS_AGENT_MARSAPOLLO_H
