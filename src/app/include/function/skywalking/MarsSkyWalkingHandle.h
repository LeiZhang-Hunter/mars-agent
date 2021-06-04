//
// Created by zhanglei on 2021/6/1.
//

#ifndef MARS_AGENT_MARSSKYWALKINGHANDLE_H
#define MARS_AGENT_MARSSKYWALKINGHANDLE_H

#include <memory>
#include <grpcpp/grpcpp.h>
#include "Noncopyable.h"
#include "os/UnixThread.h"
#include "event/Channel.h"
#include "MarsSkyWalkingConfig.h"

namespace grpc {
    class Channel;
}

namespace function {
    namespace skywalking {
        class MarsSkyWalkingHandle : public std::enable_shared_from_this<MarsSkyWalkingHandle>, public Noncopyable {
        public:
            MarsSkyWalkingHandle(const std::shared_ptr<MarsSkyWalkingConfig>& config_,
                    const std::shared_ptr<OS::UnixThread>& thread_);

            /**
             * 注册到skywalking的apm
             * @return
             */
            bool reg(const std::string& serviceName);

            /**
             * skywalking的心跳包
             * @return
             */
            bool ping();

            std::string getRegToken()
            {
                return regString;
            }

            std::string getInstanceId()
            {
                return instanceId;
            }

            std::string getUuid()
            {
                return uuid;
            }

        private:
            std::shared_ptr<MarsSkyWalkingConfig> config;

            unsigned int serviceId;

            std::string instanceId;

            std::string uuid;

            std::string regString;

            std::shared_ptr<OS::UnixThread> thread;

            std::shared_ptr<Event::Channel> pingChannel;

            std::shared_ptr<grpc::Channel> grpcChannel;
        };
    }
}
#endif //MARS_AGENT_MARSSKYWALKINGHANDLE_H
