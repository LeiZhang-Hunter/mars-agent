//
// Created by zhanglei on 2021/6/6.
//
extern "C" {
#include "evhttp.h"
}
#include "common/MarsJson.h"
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
        notificationsUrl += appList[i].appId;
        notificationsUrl += "&cluster=";
        notificationsUrl += appList[i].cluster;
        notificationsUrl += "&notifications=";
        notificationsUrl += common::MarsJson::jsonEncode(namespaces);
        struct evkeyvalq *head = evhttp_request_get_output_headers(req);
        evhttp_add_header(head, "Host", config->getServer().c_str());
        evhttp_make_request(conn, req, EVHTTP_REQ_GET, notificationsUrl.c_str());
    }

}

void apollo::MarsApolloClient::onNotifications(struct evhttp_request *req, void *arg) {
    int code = evhttp_request_get_response_code(req);
    return;
}

void apollo::MarsApolloClient::run() {
    initLocalNamespaces();

}