//
// Created by zhanglei on 2021/4/16.
//

#ifndef MARS_AGENT_MARSPROMETHEANCONFIG_H
#define MARS_AGENT_MARSPROMETHEANCONFIG_H
namespace function {
    namespace promethean {
        class MarsPrometheanConfig {
        public:
            std::string unix_path;
            std::string http_path = "/metrics";

            //处理句柄
            std::shared_ptr<http::MarsHttpAction> action;

            void load (const YAML::Node& node);
        };
    }
}
#endif //MARS_AGENT_MARSPROMETHEANCONFIG_H
