//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSPROCESSHEALTH_H
#define MARS_AGENT_MARSPROCESSHEALTH_H

#include "os/UnixCurrentThread.h"
#include "function/http/MarsHttpResponse.h"

namespace OS {
    class UnixPidFile;
}

namespace function {
    namespace health {
        class MarsProcessHealth {
        public:
            MarsProcessHealth(const std::string& pid_file);
            void handle(struct evhttp_request *request, const std::shared_ptr<function::http::MarsHttpResponse>& response);

        private:
            std::string processPidFile;
        };
    }
}
#endif //MARS_AGENT_MARSPROCESSHEALTH_H
