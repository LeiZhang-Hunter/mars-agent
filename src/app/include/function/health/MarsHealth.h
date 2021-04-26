//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSHEALTH_H
#define MARS_AGENT_MARSHEALTH_H

#include <memory>

#include "MarsFunctionObject.h"


namespace app {
    class NodeAgent;
}

namespace function {

    namespace http {
        class MarsHttpRouter;
    }

    namespace health {
        class MarsHealth : public MarsFunctionObject {
        public:
            MarsHealth(const std::shared_ptr<app::NodeAgent> &agent);

            void initFunction();

            void shutdownFunction();

            ~MarsHealth();

        private:
            std::shared_ptr<http::MarsHttpRouter> router;
        };
    }
}

#endif //MARS_AGENT_MARSHEALTH_H
