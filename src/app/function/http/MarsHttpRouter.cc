//
// Created by zhanglei on 2021/4/24.
//

#include <vector>

#include "common/MarsStringTool.h"
#include "MarsHttpRouter.h"
#include "MarsHttpAction.h"
#include "MarsRouterParser.h"
#include "MarsHttpAttributes.h"

using namespace function;

MarsHttpRouter::MarsHttpRouter() {
    groupAttributes = std::shared_ptr<MarsHttpAttributes>();
    stringTool = std::shared_ptr<common::MarsStringTool>();
}

std::shared_ptr<MarsHttpRouter> MarsHttpRouter::getRequest(const std::string& uri, std::shared_ptr<MarsHttpAction>& action) {
    this->addRoute({"GET", "HEAD"}, uri, action);
    return shared_from_this();
}

std::shared_ptr<MarsHttpRouter> MarsHttpRouter::postRequest(const std::string& uri, std::shared_ptr<MarsHttpAction>& action) {
    this->addRoute({"POST"}, uri, action);
    return shared_from_this();
}


std::shared_ptr<MarsHttpRouter> MarsHttpRouter::putRequest(const std::string& uri, std::shared_ptr<MarsHttpAction>& action) {
    this->addRoute({"PUT"}, uri, action);
    return shared_from_this();
}


std::shared_ptr<MarsHttpRouter> MarsHttpRouter::patchRequest(const std::string& uri, std::shared_ptr<MarsHttpAction>& action) {
    this->addRoute({"PATCH"}, uri, action);
    return shared_from_this();
}


std::shared_ptr<MarsHttpRouter> MarsHttpRouter::deleteRequest(const std::string& uri, std::shared_ptr<MarsHttpAction>& action) {
    this->addRoute({"DELETE"}, uri, action);
    return shared_from_this();
}


std::shared_ptr<MarsHttpRouter> MarsHttpRouter::optionsRequest(const std::string& uri, std::shared_ptr<MarsHttpAction>& action) {
    this->addRoute({"OPTIONS"}, uri, action);
    return shared_from_this();
}


std::shared_ptr<MarsHttpRouter> MarsHttpRouter::anyRequest(const std::string& uri, std::shared_ptr<MarsHttpAction>& action) {
    this->addRoute({"GET", "HEAD", "POST", "PUT", "PATCH", "DELETE"}, uri, action);
    return shared_from_this();
}

void function::MarsHttpRouter::group(const std::shared_ptr<MarsHttpAttributes> &attributes,
           const std::function<void(std::shared_ptr<MarsHttpRouter>)> &callback) {
    std::shared_ptr<MarsHttpAttributes> parentGroupAttributes = groupAttributes;

    groupAttributes->prefixStr = groupAttributes->prefixStr + "/" + attributes->prefixStr;

    groupAttributes->middlewareStr = groupAttributes->middlewareStr + "|" + attributes->middlewareStr;

    groupAttributes->namespaceStr = groupAttributes->namespaceStr + "\\" + attributes->namespaceStr;

    callback(shared_from_this());

    groupAttributes = parentGroupAttributes;
}

std::shared_ptr<function::MarsHttpRouter>
function::MarsHttpRouter::addRoute(const std::vector<std::string> &method, const std::string &uri,
         const std::shared_ptr<function::MarsHttpAction> &action) {
    std::string urlPath;
    urlPath.assign(uri);
    stringTool->strTolower(urlPath);

    if (!groupAttributes->prefixStr.empty()) {
        urlPath += stringTool->trimString(groupAttributes->prefixStr, "/") + "/" + stringTool->trimString(urlPath, "/");
    }
}

bool MarsHttpRouter::dispatch() {

}

bool function::MarsHttpRouter::initDispatcher() {

}