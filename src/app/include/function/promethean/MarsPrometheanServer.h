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
namespace function {
    namespace promethean {
        class MarsPrometheanConfig;
        class MarsPrometheanClient;

    class MarsPrometheanServer : public Noncopyable, public std::enable_shared_from_this<MarsPrometheanServer>{
        public:
            MarsPrometheanServer(const std::shared_ptr<OS::UnixThreadContainer>& container,
                    const std::shared_ptr<MarsPrometheanConfig>& config);

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
            //线程池
            std::shared_ptr<OS::UnixThreadContainer> container;
            std::shared_ptr<MarsPrometheanConfig> config;
        };
    }
}


#endif //MARS_AGENT_MARSPROMETHEANSERVER_H
