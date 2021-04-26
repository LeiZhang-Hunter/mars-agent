//
// Created by zhanglei on 2021/4/23.
//

#ifndef MARS_AGENT_MARSHTTPSERVER_H
#define MARS_AGENT_MARSHTTPSERVER_H

#include <string>
#include <memory>

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

        class MarsHttpServer {
        public:
            MarsHttpServer(const std::shared_ptr<config::MarsConfig> &marsConfig,
                           const std::shared_ptr<app::NodeAgent> &agent);

            bool regClosure();

            static void httpRequestHandle(struct evhttp_request *, void *);

            ~MarsHttpServer() {

            }

        private:
            std::string httpIp;
            short httpPort;
            std::shared_ptr<Event::EventLoop> bindLoop;
            //http的基础事例
            struct evhttp *httpBase;
            //路由
            std::shared_ptr<MarsHttpRouter> routerHandle;
            std::shared_ptr<app::NodeAgent> nodeAgent;
        };
    }
}

#endif //MARS_AGENT_MARSHTTPSERVER_H
