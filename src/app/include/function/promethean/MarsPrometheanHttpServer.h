//
// Created by zhanglei on 2021/5/8.
//

#ifndef MARS_AGENT_MARSPROMETHEANHTTPSERVER_H
#define MARS_AGENT_MARSPROMETHEANHTTPSERVER_H
extern "C" {
#include "evhttp.h"
}
namespace function {
    namespace http {
        class MarsHttpResponse;
    }
    namespace promethean {
        class MarsPrometheanHttpServer {
        public:
            void handle(struct evhttp_request *request,
                                              const std::shared_ptr<function::http::MarsHttpResponse> &response);
        };
    }
}

#endif //MARS_AGENT_MARSPROMETHEANHTTPSERVER_H
