//
// Created by zhanglei on 2021/5/20.
//

#ifndef MARS_AGENT_MARSSKYWALKING_H
#define MARS_AGENT_MARSSKYWALKING_H
#include <memory>
#include "MarsFunctionObject.h"
namespace app {
    class NodeAgent;
}

namespace config {
    class MarsConfig;
}

namespace Event {
    class EventLoop;
}
namespace function {
    namespace skywalking {
        class MarsSkyWalking
                : public function::MarsFunctionObject, public std::enable_shared_from_this<MarsSkyWalking> {
        public:
            MarsSkyWalking(const std::shared_ptr<app::NodeAgent> &agent);
            void initFunction();

            void shutdownFunction();
            ~MarsSkyWalking() {

            }
        };
    }
}

#endif //MARS_AGENT_MARSSKYWALKING_H
