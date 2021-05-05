//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSHTTPSERVERHEALTH_H
#define MARS_AGENT_MARSHTTPSERVERHEALTH_H
extern "C" {
#include "evhttp.h"
}

#include <string>
#include <memory>
#include "function/health/MarsProcessHealth.h"
#include "function/http/MarsHttpResponse.h"
namespace function {
    namespace health {

        class MarsHttpServerHealth {
        public:
            void handle(struct evhttp_request *request, const std::shared_ptr<function::http::MarsHttpResponse>& response);
        };
    }
}

#endif //MARS_AGENT_MARSHTTPSERVERHEALTH_H
