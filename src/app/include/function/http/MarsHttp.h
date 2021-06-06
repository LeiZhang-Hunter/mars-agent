//
// Created by zhanglei on 2021/4/23.
//

#ifndef MARS_AGENT_MARSHTTP_H
#define MARS_AGENT_MARSHTTP_H

#include <string>
#include <memory>
#include <unordered_set>

#include "MarsFunctionObject.h"

namespace app {
    class NodeAgent;
}

namespace config {
    class MarsConfig;
}

namespace Event {
    class EventLoop;
}

namespace function {
    namespace http {
        class MarsHttpRouter;

        class MarsHttp : public function::MarsFunctionObject,
                         public std::enable_shared_from_this<MarsHttp> {
        public:

            MarsHttp(const std::shared_ptr<app::NodeAgent> &agent);

            void initFunction();

            void httpThreadInit(const std::shared_ptr<Event::EventLoop> &threadLoop);

            void shutdownFunction();

            std::shared_ptr<MarsHttpRouter>& getRouter() {
                return routerHandle;
            }

            static void httpRequestHandle(struct evhttp_request *, void *);

            std::shared_ptr<app::NodeAgent> getMainAgent() {
                return nodeAgent;
            }


            ~MarsHttp() {
            }

        private:

            std::string getHttpRequestType(short type);

            std::string httpIp;
            short httpPort;
            int httpTimeout;
            std::shared_ptr<Event::EventLoop> bindLoop;
            //http的基础事例
            //路由
            std::shared_ptr<MarsHttpRouter> routerHandle;
            std::shared_ptr<app::NodeAgent> nodeAgent;
            struct evhttp *httpBase;
        };
    }
}

#endif //MARS_AGENT_MARSHTTP_H
