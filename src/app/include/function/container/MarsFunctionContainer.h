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

namespace function {
    namespace container {
        class MarsFunctionContainer : public interface::MarsContainerInterface {
            typedef std::map<std::string, std::shared_ptr<function::MarsFunctionObject>> ContainerMap;
        public:
            std::shared_ptr<function::MarsFunctionObject> get(const std::string &id);

            bool has(const std::string &id);

            bool bind(const std::string &id, const std::shared_ptr<function::MarsFunctionObject> &server);

        private:

            /**
             * 绑定列表
             */
            ContainerMap httpServerContainer;

        };

        std::shared_ptr<function::MarsFunctionObject> MarsFunctionContainer::get(const std::string &id) {

            if (id.empty()) {
                return std::shared_ptr<function::MarsFunctionObject>();
            }

            auto instance = httpServerContainer.find(id);
            if (instance != httpServerContainer.end()) {
                return std::shared_ptr<function::MarsFunctionObject>();
            }

            return instance->second;
        }

        bool MarsFunctionContainer::has(const std::string &id) {

            if (id.empty()) {
                return false;
            }

            auto instance = httpServerContainer.find(id);
            return instance != httpServerContainer.end();
        }

        bool MarsFunctionContainer::bind(const std::string &id,
                                         const std::shared_ptr<function::MarsFunctionObject> &server) {
            if (id.empty()) {
                return false;
            }
            auto instance = httpServerContainer.find(id);
            return !(instance != httpServerContainer.end());
        }

    }
}


#endif //MARS_AGENT_MARSCONTAINER_H
