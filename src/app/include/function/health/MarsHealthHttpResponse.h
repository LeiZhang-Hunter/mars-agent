//
// Created by zhanglei on 2021/5/6.
//

#ifndef MARS_AGENT_MARSHEALTHHTTPRESPONSE_H
#define MARS_AGENT_MARSHEALTHHTTPRESPONSE_H
#include <memory>
namespace function {
    namespace http {
    class MarsHealthHttpResponse : public std::enable_shared_from_this<MarsHealthHttpResponse>{
        public:
            MarsHealthHttpResponse() {

            }

            struct evhttp_connection *connection;
            std::shared_ptr <function::http::MarsHttpResponse> response;

            void tie(const std::shared_ptr <MarsHealthHttpResponse> &obj) {
                tie_ = obj;
            }

            void destroy() {
                if (tie_) {
                    tie_.reset();
                }
            }

            ~MarsHealthHttpResponse() {

            }
        private:
            std::shared_ptr <MarsHealthHttpResponse> tie_;
        };
    }
}

#endif //MARS_AGENT_MARSHEALTHHTTPRESPONSE_H
