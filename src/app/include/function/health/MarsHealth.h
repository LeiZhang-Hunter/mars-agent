//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSHEALTH_H
#define MARS_AGENT_MARSHEALTH_H

#include <memory>

#include "MarsFunctionObject.h"

namespace YAML {
    class Node;
}

namespace app {
    class NodeAgent;
}

namespace function {

    namespace http {
        class MarsHttpRouter;
    }

    namespace health {

        class MarsHealthConfig;

        class MarsHealth : public MarsFunctionObject {
        public:
            MarsHealth(const std::shared_ptr<app::NodeAgent> &agent);

            //初始化
            void initFunction();

            //结束
            void shutdownFunction();

            ~MarsHealth();

        private:
            //加载配置
            bool loadConfig(const YAML::Node& yamlConfig);
            //路由
            std::shared_ptr<http::MarsHttpRouter> router;
            //配置文件
            std::map<std::string, std::shared_ptr<MarsHealthConfig>> healthConfig;
        };
    }
}

#endif //MARS_AGENT_MARSHEALTH_H
