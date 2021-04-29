//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSPROCESSHEALTH_H
#define MARS_AGENT_MARSPROCESSHEALTH_H
namespace function {
    namespace health {
        class MarsProcessHealth
        {
        public:
            std::string handle(struct evhttp_request *request) {
                return "ok";
            }
        };
    }
}
#endif //MARS_AGENT_MARSPROCESSHEALTH_H
