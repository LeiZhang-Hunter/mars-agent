//
// Created by zhanglei on 2021/4/24.
//

#ifndef MARS_AGENT_MARSHTTPACTION_H
#define MARS_AGENT_MARSHTTPACTION_H
extern "C" {
#include "evhttp.h"
}

#include <memory>
#include <functional>
#include <string>

namespace function {
    namespace http {

        class MarsHttpResponse;

        typedef std::function<void(struct evhttp_request *request,
                                   const std::shared_ptr<MarsHttpResponse> &response)> usesClosure;

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
