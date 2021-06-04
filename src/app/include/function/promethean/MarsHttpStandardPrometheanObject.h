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

            //解析标准的http协议
            void parser(const std::string& content);

        private:
            //消息体
            struct HttpBody {
                std::string url;
                uint64_t startTime = 0;
                uint64_t endTime = 0;
                std::string peer;
                int responseCode = 0;
                uint64_t responseSize = 0;
                std::string path;
                std::string method;
                std::string exception;
                std::string component;
            };

            //应用信息
            struct AppInfo {
                uint32_t application_instance;
                pid_t pid;
                int32_t application_id;
                bool isEntry;
                HttpBody body;
                std::string uuid;
                std::string version;
            };

            //解析应用信息
            bool parseAppInfo(AppInfo &AppInfo, const Json::Value& jsonData);

            //获取错误码对应的值的含义
            std::string income(int responseCode);

            std::shared_ptr<promethean::MarsPrometheanObject> prometheanObject;
            prometheus::Histogram::BucketBoundaries httpServerRTBucketInfo = {0.001, 0.01, 0.05, 0.1, 0.25, 0.5, 0.75, 1, 5, 10, 20};
            prometheus::Histogram::BucketBoundaries httpServerRequestSizeBucketInfo = {1000, 3000, 5000, 7000, 10000, 15000};
        };
    }
}

#endif //MARS_AGENT_MARSHTTPSTANDARDPROMETHEANOBJECT_H
