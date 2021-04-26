//
// Created by zhanglei on 2021/4/23.
//

#ifndef MARS_AGENT_MARSCONTAINER_H
#define MARS_AGENT_MARSCONTAINER_H

#include "MarsFunctionObject.h"
#include "function/interface/MarsContainerInterface.h"
#include <map>
#include <string>
#include <memory>

namespace config {
    class MarsConfig;
}

namespace function {
    namespace container {
        class MarsFunctionContainer : public interface::MarsContainerInterface {
            typedef std::map<std::string, std::shared_ptr<function::MarsFunctionObject>> ContainerMap;
        public:
            std::shared_ptr<function::MarsFunctionObject> get(const std::string &id);

            bool has(const std::string &id);

            bool bind(const std::string &id, const std::shared_ptr<function::MarsFunctionObject> &server);

            bool init(const std::shared_ptr<config::MarsConfig>& marsConfig);

            ContainerMap getMap() {
                return containerMap;
            }

        private:

            /**
             * 绑定列表
             */
            ContainerMap containerMap;

        };
    }
}


#endif //MARS_AGENT_MARSCONTAINER_H
