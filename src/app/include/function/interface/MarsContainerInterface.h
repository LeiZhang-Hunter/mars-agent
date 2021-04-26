//
// Created by zhanglei on 2021/4/23.
//

#ifndef MARS_AGENT_MARSCONTAINERINTERFACE_H
#define MARS_AGENT_MARSCONTAINERINTERFACE_H

#include <memory>

namespace function {

    namespace interface {
        class MarsContainerInterface {
        public:
            virtual std::shared_ptr<function::MarsFunctionObject> get(const std::string &id) {
                return std::shared_ptr<function::MarsFunctionObject>();
            }

            virtual bool has(const std::string &id) {
                return true;
            }

            virtual bool bind(const std::string &id, const std::shared_ptr<function::MarsFunctionObject>& server) {
                return true;
            }
        };
    }
}

#endif //MARS_AGENT_MARSCONTAINERINTERFACE_H
