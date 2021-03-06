//
// Created by zhanglei on 2021/6/6.
//

#include "NodeAgent.h"
#include "config/MarsConfig.h"
#include "apollo/MarsApollo.h"
using namespace function;
apollo::MarsApollo::MarsApollo(const std::shared_ptr<app::NodeAgent> &agent)
:apolloConfig(std::make_shared<MarsApolloConfig>()) {
    if (!agent) {
        return;
    }
    std::shared_ptr<config::MarsConfig>& marsConfig = agent->getMarsConfig();
    //加载配置
    YAML::Node apolloNode;
    try {
        apolloNode = marsConfig->getYamlCore()[APOLLO_MODULE_NAME];
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
        return;
    }
    apolloConfig->load(apolloNode);
    apolloClient = std::make_shared<MarsApolloClient>(apolloConfig);
}

void apollo::MarsApollo::initFunction() {
    if (checkInit()) {
        return;
    }

    apolloClient->run();

    initConfirm();
}

void apollo::MarsApollo::finishFunction() {

}

void apollo::MarsApollo::shutdownFunction() {

}