//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSHEALTHCONFIG_H
#define MARS_AGENT_MARSHEALTHCONFIG_H

#include <string>

namespace function {
    namespace health {
        class MarsHealthConfig {
        public:
            std::string health_way;
            std::string health_path;
            std::string health_enable = false;
            short health_port = 9000;
            std::string health_ip = "0.0.0.0";
        };
    }
}
#endif //MARS_AGENT_MARSHEALTHCONFIG_H
