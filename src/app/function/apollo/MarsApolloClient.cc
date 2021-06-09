//
// Created by zhanglei on 2021/6/6.
//
extern "C" {
#include "evhttp.h"
}

#include <iostream>

#include "common/MarsJson.h"
#include "common/MarsStringTool.h"
#include "http/MarsHttpResponse.h"
#include "apollo/MarsApolloClient.h"

using namespace function;

std::vector<std::pair<std::string, int>>& apollo::MarsApolloClient::initLocalNamespaces()
{
    if (!localNamespaces.empty()) {
        return localNamespaces;
    }

    std::vector<apolloAppConfig> appList = config->getAppConfig();
    for (size_t i = 0; i < appList.size(); i++) {
        struct evhttp_request *req;
        struct evhttp_connection *conn;
        conn = evhttp_connection_new(config->getServer().c_str(), config->getPort());
        req = evhttp_request_new(onNotifications, this);
        std::string notificationsUrl = config->getNotificationsUrl();
        Json::Value namespaces;

        for (size_t index = 0; index < appList[i].localNamespaces.size(); index++) {
            Json::Value namespaceData;
            namespaceData["namespaceName"] = appList[i].localNamespaces[index].first;
            namespaceData["notificationId"] = appList[i].localNamespaces[index].second;
            namespaces.append(namespaceData);
        }

        ;
        notificationsUrl += "?appId=";
        notificationsUrl += common::MarsStringTool::UrlEncode(appList[i].appId);
        notificationsUrl += "&cluster=";
        notificationsUrl += common::MarsStringTool::UrlEncode(appList[i].cluster);
        notificationsUrl += "&notifications=";
        notificationsUrl += common::MarsStringTool::UrlEncode(common::MarsJson::jsonEncode(namespaces));

        std::cout << config->getHost() << std::endl;
        auto tmpResponse =  std::make_shared<http::MarsHealthHttpResponse>();
        tmpResponse->response = response;
        tmpResponse->connection = conn;
        struct evkeyvalq *head = evhttp_request_get_output_headers(req);
        evhttp_add_header(head, "Host", config->getHost().c_str());
        evhttp_add_header(head, "Connection", "keep-alive");
        evhttp_make_request(conn, req, EVHTTP_REQ_GET, notificationsUrl.c_str());
        struct timeval tv;
        tv.tv_sec = 3;
        tv.tv_usec = 0;
        evhttp_connection_set_timeout_tv(conn, &tv);
    }

}

void apollo::MarsApolloClient::onNotifications(struct evhttp_request *req, void *arg) {
    //超时断开连接了
    if (!req) {
        return;
    }
    int code = evhttp_request_get_response_code(req);
    auto client = static_cast<MarsApolloClient*>(arg);
    std::cout << code << std::endl;
    evhttp_connection_free(req->evcon);
    return;
}

void apollo::MarsApolloClient::run() {
    initLocalNamespaces();

}