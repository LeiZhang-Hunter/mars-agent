//
// Created by zhanglei on 2021/5/22.
//

#ifndef MARS_AGENT_MARSHTTPSTANDARDPROMETHEANOBJECT_H
#define MARS_AGENT_MARSHTTPSTANDARDPROMETHEANOBJECT_H
#include <string>
#include <memory>

namespace common {
    class MarsJson;
    class MarsStringTool;
}

namespace function {
    namespace promethean {
        class MarsPrometheanObject;
        class MarsHttpStandardPrometheanObject {
        public:
            MarsHttpStandardPrometheanObject(const std::shared_ptr<promethean::MarsPrometheanObject> &object);

            void parser(const std::string& content);

        private:
            struct HttpBody {
                std::string url;
                uint64_t startTime;
                uint64_t endTime;
                std::string peer;
                int responseCode;
                uint64_t responseSize;
                std::string path;
                std::string method;
                std::string exception;
                std::string component;
            };

            bool makeBody(HttpBody &body, const Json::Value& jsonBody);

            std::shared_ptr<common::MarsJson> jsonParser;
            std::shared_ptr<promethean::MarsPrometheanObject> prometheanObject;
            std::shared_ptr<common::MarsStringTool> stringParser;
        };
    }
}

#endif //MARS_AGENT_MARSHTTPSTANDARDPROMETHEANOBJECT_H
