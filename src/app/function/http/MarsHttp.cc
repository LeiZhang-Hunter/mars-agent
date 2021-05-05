//
// Created by zhanglei on 2021/4/23.
//
extern "C" {
#include "evhttp.h"
#include "event2/http.h"
#include <unistd.h>
#include <sys/syscall.h>
}

#include <cstring>
#include <iostream>
#include <memory>
#include <arpa/inet.h>
#include <zconf.h>

#include "function/http/MarsHttp.h"
#include "config/MarsConfig.h"
#include "function/http/MarsHttpRouter.h"
#include "NodeAgent.h"
#include "function/http/MarsHttpAction.h"
#include "function/http/MarsHttpResponse.h"
#include "os/UnixThreadContainer.h"

using namespace function::http;
using namespace std::placeholders;

MarsHttp::MarsHttp(const std::shared_ptr<app::NodeAgent> &agent) {
    std::shared_ptr<config::MarsConfig> marsConfig = agent->getMarsConfig();
    httpIp = marsConfig->getHttpIp();
    httpPort = static_cast<short>(marsConfig->getHttpPort());
    bindLoop = agent->getLoop();
    routerHandle = std::make_shared<MarsHttpRouter>();
    nodeAgent = agent;
    httpTimeout = marsConfig->getHttpTimeout();
    httpServerSocket = createHttpServerSocket();
}

int MarsHttp::createHttpServerSocket() {
    int ret, server_socket, opt = 1;
    server_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);//NOTE 多线程evhttp必须非阻塞
    if (server_socket < 0) {
        std::cerr << "ERROR get socket: " << server_socket << "\n" << std::endl;
        exit(-1);
    }

    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(httpIp.c_str());;
    addr.sin_port = htons(httpPort);
    ret = bind(server_socket, (struct sockaddr *) &addr, sizeof(struct sockaddr));
    if (ret < 0) {
        std::cerr << "ERROR bind socket: " << server_socket << "\n" << std::endl;
        exit(-1);
    }

    listen(server_socket, 65535);
    return server_socket;
}

void MarsHttp::initFunction() {
    nodeAgent->getUnixThreadContainer()->setThreadInitCallable(
            std::bind(&MarsHttp::httpThreadInit, shared_from_this(), _1));
}

void MarsHttp::httpThreadInit(const std::shared_ptr<Event::EventLoop> &threadLoop) {
    struct event_base *base = event_base_new();
    struct evhttp *httpBase;
    int ret;

    httpBase = evhttp_new(threadLoop->getEventBase());
    ret = evhttp_accept_socket(httpBase, httpServerSocket);
    std::cout << "ret:" << ret << std::endl;

    if (ret!=0)
        std::cerr << ("Error evhttp_accept_socket\n") << std::endl;

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

