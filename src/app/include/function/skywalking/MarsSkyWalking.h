//
// Created by zhanglei on 2021/5/20.
//

#ifndef MARS_AGENT_MARSSKYWALKING_H
#define MARS_AGENT_MARSSKYWALKING_H
#include <memory>
#include "NodeAgent.h"
#include "os/UnixThread.h"
#include "MarsFunctionObject.h"
#include "MarsSkyWalkingConfig.h"
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
            void finishFunction();
            void shutdownFunction();
            std::string regSkyWalking();
            ~MarsSkyWalking() {

            }

        private:
            std::shared_ptr<MarsSkyWalkingConfig> config;
            std::shared_ptr<OS::UnixThread> thread;
            std::string appRegString;
            std::shared_ptr<MarsSkyWalkingConfig> skywalkingConfig;
        };
    }
}

#endif //MARS_AGENT_MARSSKYWALKING_H
