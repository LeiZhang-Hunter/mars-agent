//
// Created by zhanglei on 2021/5/9.
//

#ifndef MARS_AGENT_MARSPROMETHEANCLIENT_H
#define MARS_AGENT_MARSPROMETHEANCLIENT_H

#include <memory>
#include <vector>
#include <unordered_set>

#include "event/TimingWheel.h"
#include "event/Channel.h"


namespace common {
    class MarsJson;
}

namespace function {
    namespace promethean {
        class BizPrometheanObject;

        class MarsHttpStandardPrometheanObject;

        class MarsPrometheanObject;

        class MarsPrometheanClient : public std::enable_shared_from_this<MarsPrometheanClient>, public Event::TimingWheelClient {

            enum {
                REG = 0x01,
                HTTP_STANDARD = 0x02,
                CUSTOMER = 0x03,
            };

        public:
            MarsPrometheanClient(int fd, const std::shared_ptr<MarsPrometheanObject> &object,
                                 const std::shared_ptr<MarsPrometheanConfig> &config);

            void onRead(struct bufferevent *bev, void *ctx);

            void onWrite(struct bufferevent *bev, void *ctx) {

            }

            void onClose(struct bufferevent *bev, Event::Channel *ctx);

            void parse(std::string &msg);

            void setWheelPtr(const Event::timingWheelPtr &wheelPtr_);

            ~MarsPrometheanClient() {
                std::cout << "~MarsPrometheanClient" << std::endl;
                buffer.clear();
            }

            void close();
        private:

            std::string buffer;
            bool runStatus = true;
            int clientFd;
            int count = 0;
            std::shared_ptr<BizPrometheanObject> bizParser;
            std::shared_ptr<MarsHttpStandardPrometheanObject> httpParser;
            size_t maxBufferSize;
            Event::timingWheelPtr wheelPtr;
            Event::timingWheelObjectWeakPtr wheelClientWeakPtr;
        };
    }
}

#endif //MARS_AGENT_MARSPROMETHEANCLIENT_H
