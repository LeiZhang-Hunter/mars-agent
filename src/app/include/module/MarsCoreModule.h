//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSCOREMODULE_H
#define MARS_AGENT_MARSCOREMODULE_H

#include <functional>
#include <memory>

#include "function/MarsFunctionName.h"

namespace app {
    class NodeAgent;
}

namespace config {
    class MarsConfig;
}

namespace function {
    namespace container {
        class MarsFunctionContainer;
    }

    namespace http {
        class MarsHttp;
    }
}

namespace module {
    class MarsCoreModule {
    typedef std::shared_ptr<function::container::MarsFunctionContainer> ContainerType;

    public:
        MarsCoreModule(const std::shared_ptr<app::NodeAgent>& agent);

        ContainerType getContainer() {
            return container;
        }

        std::shared_ptr<function::http::MarsHttp> getHttpObject();

        //初始化模块
        void moduleInit();

        //销毁模块
        void moduleDestroy();

        ~MarsCoreModule();

    private:
        //容器
        ContainerType container;

        std::shared_ptr<app::NodeAgent> nodeAgent;

        std::string apolloModuleName = APOLLO_MODULE_NAME;

        std::string eurekaModuleName = EUREKA_MODULE_NAME;

        std::string healthModuleName = HEALTH_MODULE_NAME;

        std::string httpModuleName = HTTP_MODULE_NAME;

        std::string prometheanModuleName = PROMETHEAN_MODULE_NAME;

        std::string wheelModuleName = WHEEL_MODULE_NAME;

        std::string jobModuleName = JOB_MODULE_NAME;

        //加载apollo
        void loadApollo();

        //加载eureka
        void loadEureka();

        //加载健康检查
        void loadHealth();

        //加载http内核
        void loadHttp();

        //加载系统勘察
        void loadOs();

        //加载普罗米休息
        void loadPromethean();

        void loadWheel();

        void loadJob();
    };
}

#endif //MARS_AGENT_MARSCOREMODULE_H
