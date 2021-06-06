//
// Created by zhanglei on 2021/4/26.
//
#include <iostream>
#include "function/health/MarsHttpServerHealth.h"
#include "function/health/MarsHealthHttpResponse.h"
using namespace function::health;

void http_request_done(struct evhttp_request *req, void *arg) {
    auto response = static_cast<function::http::MarsHealthHttpResponse*>(arg);
    if (!req) {
        response->response->response(200, "{\"status\":\"DOWN\"}");
        response->destroy();
        evhttp_connection_free(response->connection);
        return;
    }

    int code = evhttp_request_get_response_code(req);
    response->response->header("Content-Type", "application/json;charset=utf-8");
    if (code == 200) {
        response->response->response(200, "{\"status\":\"UP\"}");
    } else {
        response->response->response(200, "{\"status\":\"DOWN\"}");
    }
    evhttp_connection_free(response->connection);
    response->destroy();
}

MarsHttpServerHealth::MarsHttpServerHealth(const std::string &ip, short health_port,
        const std::string &health_path,
        const std::string& health_host, unsigned int health_timeout) {
    destHttpDomain = ip;
    destHttpPort = health_port;
    destHttpPath = health_path;
    destHealthHost = health_host;
    destHttpTimeout = health_timeout;
}

void MarsHttpServerHealth::handle(struct evhttp_request *request,
                                  const std::shared_ptr<function::http::MarsHttpResponse> &response) {
//    return "MarsHttpServerHealth";
    struct evhttp_request *req;
    struct evhttp_connection *conn;
    struct evhttp_connection *connection = evhttp_request_get_connection(request);
    if (!connection) {
        return;
    }
    struct event_base *base = evhttp_connection_get_base(connection);
    conn = evhttp_connection_new(destHttpDomain.c_str(), destHttpPort);
    evhttp_connection_set_base(conn, base);
    auto tmpResponse =  std::make_shared<http::MarsHealthHttpResponse>();
    tmpResponse->response = response;
    tmpResponse->connection = conn;
    //保持存活
    tmpResponse->tie(tmpResponse);
    req = evhttp_request_new(http_request_done, tmpResponse.get());
    if (!req) {
        return;
    }

    struct evkeyvalq *head = evhttp_request_get_output_headers(req);
    evhttp_add_header(head,"Host",destHealthHost.c_str());
    evhttp_make_request(conn, req, EVHTTP_REQ_GET, destHttpPath.c_str());
    if (destHttpTimeout) {
        struct timeval tv;
        tv.tv_sec = destHttpTimeout;
        tv.tv_usec = 0;
        evhttp_connection_set_timeout_tv(conn, &tv);
    }
}

