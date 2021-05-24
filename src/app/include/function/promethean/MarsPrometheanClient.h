//
// Created by zhanglei on 2021/5/9.
//

#ifndef MARS_AGENT_MARSPROMETHEANCLIENT_H
#define MARS_AGENT_MARSPROMETHEANCLIENT_H
#include <memory>
#include <vector>
#include <unordered_set>

namespace common {
    class MarsJson;
}

namespace function {
    namespace promethean {
        class BizPrometheanObject;
        class MarsHttpStandardPrometheanObject;

        class MarsPrometheanObject;
        class MarsPrometheanClient {

            enum {
                REG = 0x01,
                HTTP_STANDARD = 0x02,
                CUSTOMER = 0x03,
            };

        public:
            MarsPrometheanClient(int fd, const std::shared_ptr<MarsPrometheanObject>& object);

            void onRead(struct bufferevent *bev, void *ctx);

            void onWrite(struct bufferevent *bev, void *ctx) {

            }

            void parse(std::string& msg);

            void tie(const std::shared_ptr<MarsPrometheanClient>& tie) {
                tie_ = tie;
            }

            ~MarsPrometheanClient()
            {
                buffer.clear();
            }
        private:
            std::shared_ptr<MarsPrometheanClient> tie_;
            std::unordered_set<int, std::vector<char>> bufferSet;
            std::string buffer;
            bool runStatus = true;
            int clientFd;
            int count = 0;
            std::shared_ptr<BizPrometheanObject> bizParser;
            std::shared_ptr<MarsHttpStandardPrometheanObject> httpParser;
        };
    }
}

#endif //MARS_AGENT_MARSPROMETHEANCLIENT_H
