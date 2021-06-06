//
// Created by zhanglei on 2021/4/23.
//
extern "C" {
#include <unistd.h>
#include <sys/syscall.h>
#include "evhttp.h"
#include "event2/http.h"
#include "event2/listener.h"
}

#include <cstring>
#include <iostream>
#include <memory>
#include <arpa/inet.h>
#include <zconf.h>

#include "NodeAgent.h"
#include "config/MarsConfig.h"
#include "os/UnixThreadContainer.h"
#include "os/UnixThread.h"
#include "event/Channel.h"

#include "http/MarsHttp.h"
#include "http/MarsHttpRouter.h"
#include "http/MarsHttpAction.h"
#include "http/MarsHttpResponse.h"
#include "http/MarsHttpResponse.h"

using namespace function::http;
using namespace std::placeholders;

MarsHttp::MarsHttp(const std::shared_ptr<app::NodeAgent> &agent) {
    std::shared_ptr<config::MarsConfig>& marsConfig = agent->getMarsConfig();
    httpIp = marsConfig->getHttpIp();
    httpPort = static_cast<short>(marsConfig->getHttpPort());
    bindLoop = agent->getLoop();
    routerHandle = std::make_shared<MarsHttpRouter>();
    nodeAgent = agent;
    httpTimeout = marsConfig->getHttpTimeout();
}





void MarsHttp::initFunction() {
    int ret;
    struct evconnlistener *listener;

    httpBase = evhttp_new(bindLoop->getEventBase());
    struct evhttp_bound_socket *bound = evhttp_bind_socket_with_handle(httpBase, httpIp.c_str(), httpPort);

    if (!bound) {
        std::cerr << ("Error evhttp_accept_socket\n") << std::endl;
        exit(-1);
    }

    listener = evhttp_bound_socket_get_listener(bound);

//    设置请求超时时间(s)
    evhttp_set_timeout(httpBase, httpTimeout);

//    设置处理函数
    evhttp_set_gencb(httpBase, httpRequestHandle, this);
}

void MarsHttp::httpThreadInit(const std::shared_ptr<Event::EventLoop> &threadLoop) {

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
        response->response(HTTP_NOTFOUND, "");
        return;
    }


    //获取要处理的函数
    http::usesClosure handle = action->getUsers();
    if (handle) {
        handle(request, response);
        return;
    }

    response->response(HTTP_INTERNAL, "");
}

