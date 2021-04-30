//
// Created by zhanglei on 2021/4/24.
//

#include <vector>
#include <iostream>

#include "common/MarsStringTool.h"
#include "function/http/MarsHttpRouter.h"
#include "function/http/MarsHttpAction.h"
#include "function/http/MarsRouterParser.h"
#include "function/http/MarsHttpAttributes.h"

using namespace function::http;

MarsHttpRouter::MarsHttpRouter() {
    groupAttributes = std::make_shared<MarsHttpAttributes>();
    stringTool = std::shared_ptr<common::MarsStringTool>();
}

std::shared_ptr<MarsHttpRouter>
MarsHttpRouter::getRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action) {
    this->addRoute({"GET", "HEAD"}, uri, action);
    return shared_from_this();
}

std::shared_ptr<MarsHttpRouter>
MarsHttpRouter::postRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action) {
    this->addRoute({"POST"}, uri, action);
    return shared_from_this();
}


std::shared_ptr<MarsHttpRouter>
MarsHttpRouter::putRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action) {
    this->addRoute({"PUT"}, uri, action);
    return shared_from_this();
}


std::shared_ptr<MarsHttpRouter>
MarsHttpRouter::patchRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action) {
    this->addRoute({"PATCH"}, uri, action);
    return shared_from_this();
}


std::shared_ptr<MarsHttpRouter>
MarsHttpRouter::deleteRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action) {
    this->addRoute({"DELETE"}, uri, action);
    return shared_from_this();
}


std::shared_ptr<MarsHttpRouter>
MarsHttpRouter::optionsRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action) {
    this->addRoute({"OPTIONS"}, uri, action);
    return shared_from_this();
}


std::shared_ptr<MarsHttpRouter>
MarsHttpRouter::anyRequest(const std::string &uri, std::shared_ptr<MarsHttpAction> &action) {
    this->addRoute({"GET", "HEAD", "POST", "PUT", "PATCH", "DELETE"}, uri, action);
    return shared_from_this();
}

void MarsHttpRouter::group(const std::shared_ptr<MarsHttpAttributes> &attributes,
                           const std::function<void(std::shared_ptr<MarsHttpRouter>)> &callback) {
    std::shared_ptr<MarsHttpAttributes> parentGroupAttributes = groupAttributes;

    groupAttributes->prefixStr = groupAttributes->prefixStr + "/" + attributes->prefixStr;

    groupAttributes->middlewareStr = groupAttributes->middlewareStr + "|" + attributes->middlewareStr;

    groupAttributes->namespaceStr = groupAttributes->namespaceStr + "\\" + attributes->namespaceStr;

    callback(shared_from_this());

    groupAttributes = parentGroupAttributes;
}

std::shared_ptr<MarsHttpRouter>
MarsHttpRouter::addRoute(const std::vector<std::string> &method, const std::string &uri,
                         const std::shared_ptr<MarsHttpAction> &action) {
    std::string urlPath;
    urlPath.assign(uri);
    stringTool->strTolower(urlPath);

    if (!groupAttributes->prefixStr.empty()) {
        urlPath += stringTool->trimString(groupAttributes->prefixStr, "/") + "/" + stringTool->trimString(urlPath, "/");
    }

    addStaticRoute(method, uri, action);
    return shared_from_this();
}

void MarsHttpRouter::addStaticRoute(const std::vector<std::string> &methodVector, const std::string &uri,
                    const std::shared_ptr<MarsHttpAction> &action) {
    for (int i = 0; i < methodVector.size(); i++) {
        std::string method = methodVector[i];
        if (staticRoutes.find(method) == staticRoutes.end()) {
            staticRoutes[method][uri] = action;
            continue;
        }

        if (staticRoutes[method].find(uri) == staticRoutes[method].end()) {
            staticRoutes[method][uri] = action;
            continue;
        }
    }
}


std::shared_ptr<MarsHttpAction> MarsHttpRouter::dispatch(const std::string &method, const std::string& uri) {
    if (staticRoutes.find(method) == staticRoutes.end()) {
        return std::shared_ptr<MarsHttpAction>();
    }

    if (staticRoutes[method].find(uri) == staticRoutes[method].end()) {
        return std::shared_ptr<MarsHttpAction>();
    }
    return staticRoutes[method][uri];
}

bool MarsHttpRouter::initDispatcher() {
    return true;
}