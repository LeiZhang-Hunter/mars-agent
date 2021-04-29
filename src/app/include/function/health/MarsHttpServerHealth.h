//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSHTTPSERVERHEALTH_H
#define MARS_AGENT_MARSHTTPSERVERHEALTH_H
extern "C" {
#include "evhttp.h"
}
#include <string>
namespace function {
    namespace health {
        class MarsHttpServerHealth
        {
        public:
            std::string handle(struct evhttp_request *request);
        };
    }
}

#endif //MARS_AGENT_MARSHTTPSERVERHEALTH_H
