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

        class MarsPrometheanObject;

        class MarsPrometheanHttpServer {
        public:
            MarsPrometheanHttpServer(const std::shared_ptr<MarsPrometheanObject>& object);
            void handle(struct evhttp_request *request,
                                              const std::shared_ptr<function::http::MarsHttpResponse> &response);

        private:
            std::shared_ptr<MarsPrometheanObject> promethean;
        };
    }
}

#endif //MARS_AGENT_MARSPROMETHEANHTTPSERVER_H
