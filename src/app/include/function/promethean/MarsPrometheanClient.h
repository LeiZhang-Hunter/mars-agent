//
// Created by zhanglei on 2021/5/9.
//

#ifndef MARS_AGENT_MARSPROMETHEANCLIENT_H
#define MARS_AGENT_MARSPROMETHEANCLIENT_H
#include <memory>
#include <vector>
#include <unordered_set>
namespace function {
    namespace promethean {
        class MarsPrometheanClient {
        public:

            void onRead(struct bufferevent *bev, void *ctx);

            void onWrite(struct bufferevent *bev, void *ctx) {

            }

            void tie(const std::shared_ptr<MarsPrometheanClient>& tie) {
                tie_ = tie;
            }
        private:
            std::shared_ptr<MarsPrometheanClient> tie_;
            std::unordered_set<int, std::vector<char>> bufferSet;
        };
    }
}

#endif //MARS_AGENT_MARSPROMETHEANCLIENT_H
