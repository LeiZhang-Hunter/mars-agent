//
// Created by zhanglei on 2021/4/23.
//
extern "C" {
#include "evhttp.h"
#include "event2/http.h"
}

#include <cstring>
#include <iostream>
#include <memory>

#include "function/http/MarsHttp.h"
#include "config/MarsConfig.h"
#include "function/http/MarsHttpRouter.h"
#include "NodeAgent.h"
#include "function/http/MarsHttpAction.h"
#include "function/http/MarsHttpResponse.h"

using namespace function::http;

MarsHttp::MarsHttp(const std::shared_ptr<app::NodeAgent> &agent) {
    std::shared_ptr<config::MarsConfig> marsConfig = agent->getMarsConfig();
    httpIp = marsConfig->getHttpIp();
    httpPort = static_cast<short>(marsConfig->getHttpPort());
    bindLoop = agent->getLoop();
    httpBase = evhttp_new(bindLoop->getEventBase());
    routerHandle = std::make_shared<MarsHttpRouter>();
    nodeAgent = agent;
    httpTimeout = marsConfig->getHttpTimeout();
}

void MarsHttp::initFunction() {
//启动http服务端
    int ret = evhttp_bind_socket(httpBase, httpIp.c_str(), httpPort);

    if (ret == -1) {
        printf("====line:%d,%s;error:%s\n", __LINE__, " http server start failed.", strerror(errno));
        exit(-1);
    }

    //设置请求超时时间(s)
    evhttp_set_timeout(httpBase, httpTimeout);

    //设置处理函数
    evhttp_set_gencb(httpBase, httpRequestHandle, this);
}

void MarsHttp::shutdownFunction() {

}

std::string MarsHttp::getHttpRequestType(short type) {
    switch (type) {
        case evhttp_cmd_type::EVHTTP_REQ_GET:
            return "GET";
        case evhttp_cmd_type::EVHTTP_REQ_POST:
            return "POST";
        case evhttp_cmd_type::EVHTTP_REQ_HEAD:
            return "HEAD";
        case evhttp_cmd_type::EVHTTP_REQ_PUT:
            return "PUT";
        case evhttp_cmd_type::EVHTTP_REQ_DELETE:
            return "DELETE";
        case evhttp_cmd_type::EVHTTP_REQ_OPTIONS:
            return "OPTIONS";
        case evhttp_cmd_type::EVHTTP_REQ_TRACE:
            return "TRACE";
        case evhttp_cmd_type::EVHTTP_REQ_CONNECT:
            return "CONNECT";
        case evhttp_cmd_type::EVHTTP_REQ_PATCH:
            return "PATCH";
    }
    return "GET";
}

void MarsHttp::httpRequestHandle(struct evhttp_request *request, void *args) {
    auto httpDispatcher = static_cast<MarsHttp *>(args);
    if (!httpDispatcher) {
        return;
    }

    if (!request) {
        return;
    }

    //初始化路由
    std::shared_ptr<MarsHttpRouter> router = httpDispatcher->getRouter();
    const struct evhttp_uri *evhttp_uri = evhttp_request_get_evhttp_uri(request);
    char url[8192];
    evhttp_uri_join(const_cast<struct evhttp_uri *>(evhttp_uri), url, 8192);

    //初始化响应体
    std::shared_ptr<MarsHttpResponse> response = std::make_shared<MarsHttpResponse>(request, url);

    //查找路由
    std::shared_ptr<MarsHttpAction> action = router->dispatch(httpDispatcher->getHttpRequestType(request->type), url);
    if (!action) {
        response->response(404, "");
        return;
    }


    //获取要处理的函数
    std::function<std::string(struct evhttp_request *request)> handle = action->getUsers();
    if (handle) {
        std::string ret = handle(request);
        response->response(HTTP_OK, ret);
        return;
    }

    response->response(HTTP_INTERNAL, "");
}

