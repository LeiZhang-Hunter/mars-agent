//
// Created by zhanglei on 2021/5/22.
//
#include <iostream>
#include<cstdlib>
#include<cstdio>
#include "common/MarsJson.h"
#include "common/MarsStringTool.h"
#include "promethean/MarsPrometheanObject.h"
#include "promethean/MarsHttpStandardPrometheanObject.h"

using namespace function;

promethean::MarsHttpStandardPrometheanObject::MarsHttpStandardPrometheanObject(
        const std::shared_ptr<promethean::MarsPrometheanObject> &object) {
    prometheanObject = object;
}

bool promethean::MarsHttpStandardPrometheanObject::parseAppInfo(AppInfo &appInfo, const Json::Value& jsonData) {
    try {
        appInfo.application_instance = jsonData["application_instance"].asUInt();
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        appInfo.pid = jsonData["pid"].asInt();
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        std::string url = jsonData["application_id"].asString();
        appInfo.body.url = url;
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        std::string url = jsonData["version"].asString();
        appInfo.body.url = url;
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        appInfo.isEntry = jsonData["isEntry"].asBool();
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    //解析整个body
    Json::Value jsonBody = jsonData["body"];

    if (jsonBody.empty()) {
        std::cout << "jsonBody is empty" << std::endl;
        return false;
    }

    if (!jsonBody.isObject()) {
        std::cout << "jsonBody is not object" << std::endl;
        return false;
    }

    try {
        std::string url = jsonBody["url"].asString();
        appInfo.body.url = url;
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        uint64_t startTime = jsonBody["startTime"].asUInt64();
        appInfo.body.startTime = startTime;
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        uint64_t endTime = jsonBody["endTime"].asUInt64();
        appInfo.body.endTime = endTime;
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        std::string peer = jsonBody["peer"].asString();
        appInfo.body.peer = peer;
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        int responseCode = jsonBody["responseCode"].asInt();
        appInfo.body.responseCode = responseCode;
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        uint64_t responseSize = jsonBody["responseSize"].asUInt64();
        appInfo.body.responseSize = responseSize;
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        std::string path = jsonBody["path"].asString();
        appInfo.body.path = path;
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        std::string method = jsonBody["method"].asString();
        appInfo.body.method = method;
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        std::string exception = jsonBody["exception"].asString();
        appInfo.body.exception = exception;
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        std::string component = jsonBody["component"].asString();
        appInfo.body.component = component;
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    return true;
}

std::string promethean::MarsHttpStandardPrometheanObject::income(int responseCode) {
    if (responseCode < 200) {
        return "INFORMATIONAL";
    }

    if (responseCode < 300) {
        return "SUCCESS";
    }

    if (responseCode < 400) {
        return "REDIRECTION";
    }

    if (responseCode < 500) {
        return "CLIENT_ERROR";
    }

    return "SERVER_ERROR";
}

void promethean::MarsHttpStandardPrometheanObject::parser(const std::string &content) {
    AppInfo appInfo;

    Json::Value httpProtocol;
    try {
        common::MarsJson::jsonDecode(content, &httpProtocol);
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        return;
    }

    if (httpProtocol.empty()) {
        return;
    }

    if (!httpProtocol.isObject()) {
        return;
    }

    if (!parseAppInfo(appInfo, httpProtocol)) {
        return;
    }

    //记录http服务端
    char status[25];
    //这里使用sprintf
    sprintf(status, "%d", appInfo.body.responseCode);

    //格式化标签
    std::map<std::string, std::string> labels;
    labels["exception"] = appInfo.body.exception;
    labels["method"] = appInfo.body.method;
    labels["status"] = status;
    labels["outcome"] = income(appInfo.body.responseCode);

    //记录服务端处理耗时
    double requestTime = static_cast<double >(appInfo.body.endTime - appInfo.body.startTime);

    if (appInfo.isEntry) {
        //http服务端
        labels["uri"] = appInfo.body.path;

        //记录响应时间
        auto& serverRequestTimeHistogramVec = prometheanObject->regHistogramPacket("http_server_requests_seconds");
        auto& serverRequestTimeHistogramHandle = serverRequestTimeHistogramVec.Add(labels, httpServerRTBucketInfo);
        serverRequestTimeHistogramHandle.Observe(requestTime / 1000);

        //记录服务端处理包体大小
        auto& serverRequestSizeHistogramVec = prometheanObject->regHistogramPacket("http_server_response_size_bytes");
        auto& serverRequestSizeHistogramHandle = serverRequestSizeHistogramVec.Add(labels, httpServerRequestSizeBucketInfo);
        serverRequestSizeHistogramHandle.Observe(static_cast<double >(appInfo.body.responseSize));
    } else {
        //客户端要切割url
        std::vector<std::string> pathInfo = common::MarsStringTool::split(appInfo.body.url, "?");
        if (pathInfo.empty()) {
            labels["uri"] = "";
        } else {
            labels["uri"] = pathInfo[0];
        }
        labels["clientName"] = appInfo.body.peer;
        labels["component"] = appInfo.body.component;
        //http客户端
        auto& clientRequestTimeHistogramVec = prometheanObject->regHistogramPacket("rig_http_client_requests_seconds");
        auto& clientRequestTimeHistogramHandle = clientRequestTimeHistogramVec.Add(labels, httpServerRTBucketInfo);
        clientRequestTimeHistogramHandle.Observe(requestTime / 1000);

        auto& clientRequestSizeHistogramVec = prometheanObject->regHistogramPacket("rig_http_client_response_size_bytes");
        auto& clientRequestSizeHistogramHandle = clientRequestTimeHistogramVec.Add(labels, httpServerRequestSizeBucketInfo);
        clientRequestSizeHistogramHandle.Observe(static_cast<double >(appInfo.body.responseSize));
    }
}