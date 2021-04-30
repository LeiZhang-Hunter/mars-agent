//
// Created by zhanglei on 2021/4/24.
//

#ifndef MARS_AGENT_MARSHTTPACTION_H
#define MARS_AGENT_MARSHTTPACTION_H
extern "C" {
#include "evhttp.h"
}

#include <functional>
#include <string>

namespace function {
    namespace http {
        typedef  std::function<std::string(struct evhttp_request *request)> usesClosure;
        class MarsHttpAction {
        public:

            std::string middleware;

            void setUsers(const usesClosure &callable) {
                uses = callable;
            }

            usesClosure getUsers() {
                return uses;
            }

        private:
            usesClosure uses;
        };
    }

}

#endif //MARS_AGENT_MARSHTTPACTION_H
