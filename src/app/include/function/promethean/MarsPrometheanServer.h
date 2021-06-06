//
// Created by zhanglei on 2021/4/16.
//

#ifndef MARS_AGENT_MARSPROMETHEANSERVER_H
#define MARS_AGENT_MARSPROMETHEANSERVER_H

extern "C" {
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>
#include <arpa/inet.h>
}
#include <map>
#include <memory>
#include <unordered_map>
#include "event/TimingWheel.h"
#include "event/TimingWheelObject.h"
#include "event/Channel.h"

#include "Noncopyable.h"
#include "event/TimingWheel.h"
#include "skywalking/MarsSkyWalking.h"
namespace function {
    namespace promethean {
        class MarsPromethean;
        class MarsPrometheanConfig;
        class MarsPrometheanClient;
        class BizPrometheanObject;
        class MarsHttpStandardPrometheanObject;

    class MarsPrometheanServer : public Noncopyable, public std::enable_shared_from_this<MarsPrometheanServer>{
        public:
            MarsPrometheanServer(const std::shared_ptr<OS::UnixThreadContainer>& container,
                    const std::shared_ptr<MarsPrometheanConfig>& config,
                    const std::shared_ptr<skywalking::MarsSkyWalking>& apmServer_,
                                 const std::shared_ptr<MarsPrometheanObject>& promethean_);

            static void
            prometheanCbListener(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int len,
                                 void *ptr);

            void onIdle(struct bufferevent *bev, Event::Channel *ctx);

            void startTimingWheel();

            void bindClient(int fd,
                            promethean::MarsPromethean *promethean,
                            const std::shared_ptr<OS::UnixThread>& thread);

            ~MarsPrometheanServer();

        private:
            typedef std::unordered_map<pid_t, Event::timingWheelPtr> timingWheelStructMap;
            //时间轮算法存储的仪表盘
            timingWheelStructMap wheelMap;
            //线程池容器
            const std::shared_ptr<OS::UnixThreadContainer>& container;
            //配置
            const std::shared_ptr<MarsPrometheanConfig>& config;
            //apm的server
            std::shared_ptr<skywalking::MarsSkyWalking> apmServer;
            //普罗米修斯对象
            const std::shared_ptr<MarsPrometheanObject>& promethean;
            //自定义协议解析
            std::shared_ptr<BizPrometheanObject> bizParser;
            //http蝶衣解析
            std::shared_ptr<MarsHttpStandardPrometheanObject> httpParser;
        };
    }
}


#endif //MARS_AGENT_MARSPROMETHEANSERVER_H
