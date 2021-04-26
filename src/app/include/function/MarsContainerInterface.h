//
// Created by zhanglei on 2021/4/23.
//

#ifndef MARS_AGENT_MARSCONTAINERINTERFACE_H
#define MARS_AGENT_MARSCONTAINERINTERFACE_H

#include <memory>

namespace function {

    template <class T1>
    class MarsContainerInterface {
    public:
        virtual std::shared_ptr<T1> get(const std::string &id) {
            return std::shared_ptr<T1>();
        }

        virtual bool has(const std::string& id) {
            return true;
        }

        virtual bool bind(const std::string& id, std::shared_ptr<T1> server) {
            return true;
        }


    };
}

#endif //MARS_AGENT_MARSCONTAINERINTERFACE_H
