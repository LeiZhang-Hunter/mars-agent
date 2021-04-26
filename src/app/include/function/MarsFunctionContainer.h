//
// Created by zhanglei on 2021/4/23.
//

#ifndef MARS_AGENT_MARSCONTAINER_H
#define MARS_AGENT_MARSCONTAINER_H

#include "function/interface/MarsContainerInterface.h"
#include <map>
#include <string>
#include <memory>

namespace function {
    class MarsHttpServer;

    template<class T1>
    class MarsFunctionContainer : public interface::MarsContainerInterface<T1> {
        typedef std::map<std::string, std::shared_ptr<T1>> ContainerMap;
    public:
        std::shared_ptr<T1> get(const std::string &id);

        bool has(const std::string &id);

        bool bind(const std::string &id, std::shared_ptr<T1> server);

    private:

        /**
         * 绑定列表
         */
        ContainerMap httpServerContainer;

    };
}

template<class T1>
std::shared_ptr<T1> function::MarsFunctionContainer<T1>::get(const std::string &id) {

    if (id.empty()) {
        return std::shared_ptr<T1>();
    }

    auto instance = httpServerContainer.find(id);
    if (instance != httpServerContainer.end()) {
        return std::shared_ptr<T1>();
    }

    return instance->second;
}

template<class T1>
bool function::MarsFunctionContainer<T1>::has(const std::string &id) {

    if (id.empty()) {
        return false;
    }

    auto instance = httpServerContainer.find(id);
    return instance != httpServerContainer.end();
}

template<class T1>
bool
function::MarsFunctionContainer<T1>::bind(const std::string &id, std::shared_ptr<T1> server) {

    if (id.empty()) {
        return false;
    }

    auto instance = httpServerContainer.find(id);
    return !(instance != httpServerContainer.end());
}

#endif //MARS_AGENT_MARSCONTAINER_H
