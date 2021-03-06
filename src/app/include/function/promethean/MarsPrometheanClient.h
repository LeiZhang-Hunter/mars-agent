//
// Created by zhanglei on 2021/5/9.
//

#ifndef MARS_AGENT_MARSPROMETHEANCLIENT_H
#define MARS_AGENT_MARSPROMETHEANCLIENT_H

#include <memory>
#include <vector>
#include <unordered_set>
#include <atomic>

#include "event/TimingWheel.h"
#include "event/Channel.h"
#include "promethean/BizPrometheanObject.h"
#include "promethean/MarsHttpStandardPrometheanObject.h"
#include "promethean/MarsPrometheanObject.h"
#include "skywalking/MarsSkyWalking.h"

namespace common {
    class MarsJson;
}

namespace function {
    namespace promethean {
        static std::atomic_llong connection{ 0 };//原子数据类型

        class MarsPrometheanClient : public std::enable_shared_from_this<MarsPrometheanClient>, public Event::TimingWheelClient {
        public:
            MarsPrometheanClient(int fd, const std::shared_ptr<MarsPrometheanObject> &object,
                                 const std::shared_ptr<MarsPrometheanConfig> &config,
                                 const std::shared_ptr<skywalking::MarsSkyWalking>& apmServer_,
                                 const std::shared_ptr<BizPrometheanObject>& bizParser_,
                                 const std::shared_ptr<MarsHttpStandardPrometheanObject>& httpParser_,
                                 const Event::timingWheelPtr& wheelPtr_);

            void onRead(struct bufferevent *bev, void *ctx);

            void onWrite(struct bufferevent *bev, void *ctx) {

            }

            void onClose(struct bufferevent *bev, Event::Channel *ctx);

            ~MarsPrometheanClient();

            void close();


        private:
            //解析协议
            void parse(struct bufferevent *bev, void *ctx, std::string &msg);
            //注册
            void reg(struct bufferevent *bev, void *ctx, const std::string& content);

            std::string buffer;
            bool runStatus = true;
            int clientFd;
            int count = 0;
            const std::shared_ptr<BizPrometheanObject>& bizParser;
            const std::shared_ptr<MarsHttpStandardPrometheanObject>& httpParser;
            const std::shared_ptr<skywalking::MarsSkyWalking>& apmServer;
            size_t maxBufferSize;
            const Event::timingWheelPtr& wheelPtr;
            Event::timingWheelObjectWeakPtr wheelClientWeakPtr;
        };
    }
}

#endif //MARS_AGENT_MARSPROMETHEANCLIENT_H
