//
// Created by zhanglei on 2021/4/24.
//

#ifndef MARS_AGENT_MARSHTTPROUTER_H
#define MARS_AGENT_MARSHTTPROUTER_H

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <unordered_set>
#include <map>

namespace common {
    class MarsStringTool;
}

namespace function {
    namespace http {
        class MarsHttpAttributes;

        class MarsHttpAction;

        class MarsHttpRouter : public std::enable_shared_from_this<MarsHttpRouter> {
        public:

            MarsHttpRouter();

            std::shared_ptr<MarsHttpRouter> getRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action);

            std::shared_ptr<MarsHttpRouter>
            postRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action);

            std::shared_ptr<MarsHttpRouter> putRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action);

            std::shared_ptr<MarsHttpRouter>
            patchRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action);

            std::shared_ptr<MarsHttpRouter>
            deleteRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action);

            std::shared_ptr<MarsHttpRouter>
            optionsRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action);

            std::shared_ptr<MarsHttpRouter> anyRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action);

            void group(const std::shared_ptr<MarsHttpAttributes> &attributes,
                       const std::function<void(std::shared_ptr<MarsHttpRouter>)> &callback);


            std::shared_ptr<MarsHttpRouter>
            addRoute(const std::vector<std::string> &method, const std::string &uri,
                     const std::shared_ptr<MarsHttpAction> &action);

            std::shared_ptr<MarsHttpAction> dispatch(const std::string &uri, const std::string& method);

            bool initDispatcher();


        private:

            void addStaticRoute(const std::vector<std::string> &method, const std::string &uri,
                                const std::shared_ptr<MarsHttpAction> &action);

            uint8_t identifier = 1;

            std::shared_ptr<MarsHttpAttributes> groupAttributes;

            std::shared_ptr<common::MarsStringTool> stringTool;

            //静态集合
            std::map<std::string, std::map<std::string, std::shared_ptr<MarsHttpAction>>> staticRoutes;
        };
    }
}

#endif //MARS_AGENT_MARSHTTPROUTER_H
