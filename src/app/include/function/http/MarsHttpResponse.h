//
// Created by zhanglei on 2021/5/1.
//

#ifndef MARS_AGENT_MARSHTTPRESPONSE_H
#define MARS_AGENT_MARSHTTPRESPONSE_H

#include <string>

#include "Noncopyable.h"

namespace function {
    namespace http {
        class MarsHttpResponse : public Noncopyable {
        public:
            explicit MarsHttpResponse(struct evhttp_request *request, const char* uri);

            bool response(short code, const std::string& response);

            ~MarsHttpResponse();

        private:
            struct evhttp_request *request;

            struct evbuffer *httpBuffer;

            const char* httpUri;
        };
    }
}

#endif //MARS_AGENT_MARSHTTPRESPONSE_H
