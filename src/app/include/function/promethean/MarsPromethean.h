//
// Created by zhanglei on 2021/5/8.
//

#ifndef MARS_AGENT_MARSPROMETHEAN_H
#define MARS_AGENT_MARSPROMETHEAN_H

#include <memory>
#include "MarsFunctionObject.h"
#include <Noncopyable.h>

namespace app {
    class NodeAgent;
}
namespace function {
    namespace http {
        class MarsHttpRouter;
    }

    namespace promethean {
        class MarsPrometheanConfig;

        class MarsPrometheanObject;

        class MarsPromethean
                : public MarsFunctionObject, public std::enable_shared_from_this<MarsPromethean>, public Noncopyable {
        public:
            MarsPromethean(const std::shared_ptr<app::NodeAgent> &agent);

            void initFunction();

            void shutdownFunction();

            std::shared_ptr<app::NodeAgent> getNodeAgent() {
                return nodeAgent;
            }

            ~MarsPromethean();

        private:
            int loadUnixServer();

            static void
            prometheanCbListener(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int len,
                                 void *ptr);

            //路由
            std::shared_ptr<http::MarsHttpRouter> router;

            std::shared_ptr<MarsPrometheanConfig> prometheanConfig;

            std::shared_ptr<app::NodeAgent> nodeAgent;

            std::shared_ptr<MarsPrometheanObject> promethean;


            bool isInit = false;
        };
    }
}

#endif //MARS_AGENT_MARSPROMETHEAN_H
