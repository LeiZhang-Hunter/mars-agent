//
// Created by zhanglei on 2021/4/24.
//

#ifndef MARS_AGENT_MARSHTTPACTION_H
#define MARS_AGENT_MARSHTTPACTION_H

#include <functional>

namespace function {
    namespace http {
        class MarsHttpAction {
        public:
            std::function<void(struct evhttp_request *request)> uses;

            std::string middleware;
        };
    }

}

#endif //MARS_AGENT_MARSHTTPACTION_H
