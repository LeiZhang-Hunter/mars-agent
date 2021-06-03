//
// Created by zhanglei on 2021/6/1.
//

#ifndef MARS_AGENT_MARSSKYWALKINGHANDLE_H
#define MARS_AGENT_MARSSKYWALKINGHANDLE_H

#include <memory>
#include <grpcpp/grpcpp.h>
#include "Noncopyable.h"
#include "MarsSkyWalkingConfig.h"
namespace function {
    namespace skywalking {
        class MarsSkyWalkingHandle : public std::enable_shared_from_this<MarsSkyWalkingHandle>, public Noncopyable {
        public:
            MarsSkyWalkingHandle(const std::shared_ptr<MarsSkyWalkingConfig>& config_);

            /**
             * 注册到skywalking的apm
             * @return
             */
            bool reg();

        private:
            std::shared_ptr<MarsSkyWalkingConfig> config;

            std::string instanceId;

            std::string uuid;

            std::string regString;
        };
    }
}
#endif //MARS_AGENT_MARSSKYWALKINGHANDLE_H