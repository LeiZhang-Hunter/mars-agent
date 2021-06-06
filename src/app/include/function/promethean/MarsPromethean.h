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

        class MarsPrometheanServer;

        class MarsPromethean
                : public MarsFunctionObject, public std::enable_shared_from_this<MarsPromethean>, public Noncopyable {
        public:
            MarsPromethean(const std::shared_ptr<app::NodeAgent> &agent);

            void initFunction();

            void finishFunction();

            void shutdownFunction();

            std::shared_ptr<app::NodeAgent> getNodeAgent() {
                return nodeAgent;
            }

            std::shared_ptr<MarsPrometheanObject> getPrometheanObject() {
                return promethean;
            }

            std::shared_ptr<MarsPrometheanConfig> getConfig() {
                return prometheanConfig;
            }

            std::shared_ptr<MarsPrometheanServer> getUnixServer() {
                return prometheanServer;
            }

            ~MarsPromethean();

        private:
            bool loadUnixServer();



            //路由
            const std::shared_ptr<http::MarsHttpRouter>& router;

            //普罗米修斯的配置
            std::shared_ptr<MarsPrometheanConfig> prometheanConfig;

            //agent主类
            std::shared_ptr<app::NodeAgent> nodeAgent;

            //普罗米修斯对象
            std::shared_ptr<MarsPrometheanObject> promethean;

            //普罗米修斯unix服务端对象
            std::shared_ptr<MarsPrometheanServer> prometheanServer;

            bool isInit = false;

            bool isFinish = false;
        };
    }
}

#endif //MARS_AGENT_MARSPROMETHEAN_H
