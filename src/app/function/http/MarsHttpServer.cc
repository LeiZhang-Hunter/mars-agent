//
// Created by zhanglei on 2021/4/23.
//
extern "C" {
#include "evhttp.h"
}

#include <cstring>
#include <iostream>
#include <memory>

#include "function/http/MarsHttpServer.h"
#include "event/EventLoop.h"
#include "config/MarsConfig.h"
#include "function/http/MarsHttpRouter.h"
#include "NodeAgent.h"

using namespace function::http;

MarsHttpServer::MarsHttpServer(const std::shared_ptr<config::MarsConfig>& marsConfig,
                                         const std::shared_ptr<app::NodeAgent> &agent) {
    httpIp = marsConfig->getHttpIp();
    httpPort = static_cast<short >(marsConfig->getHttpPort());
    bindLoop = agent->getLoop();
    httpBase = evhttp_new(bindLoop->getEventBase());
    routerHandle = std::make_shared<MarsHttpRouter>();
    nodeAgent = agent;

    //启动http服务端
    int ret = evhttp_bind_socket(httpBase, httpIp.c_str(), httpPort);

    if (ret == -1) {
        printf("====line:%d,%s;error:%s\n", __LINE__," http server start failed.", strerror(errno));
        exit(-1);
    }

    //设置请求超时时间(s)
    evhttp_set_timeout(httpBase, marsConfig->getHttpTimeout());

    //设置处理函数
    evhttp_set_gencb(httpBase, httpRequestHandle, this);

}

void MarsHttpServer::httpRequestHandle(struct evhttp_request *request, void *args) {
    const struct evhttp_uri* evhttp_uri = evhttp_request_get_evhttp_uri(request);
    char url[8192];
    evhttp_uri_join(const_cast<struct evhttp_uri*>(evhttp_uri), url, 8192);
    std::cout << url << std::endl;

    struct evbuffer* evbuf = evbuffer_new();
    if (!evbuf)
    {
        printf("create evbuffer failed!\n");
        return ;
    }

    evbuffer_add_printf(evbuf, "Server response. Your request url is %s", url);
    evhttp_send_reply(request, HTTP_OK, "OK", evbuf);
    evbuffer_free(evbuf);
}

bool MarsHttpServer::regClosure() {
    return true;
}
