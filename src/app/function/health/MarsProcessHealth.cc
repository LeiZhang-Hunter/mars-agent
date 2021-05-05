//
// Created by zhanglei on 2021/4/26.
//
extern "C" {
#include "evhttp.h"
#include <fcntl.h>
}

#include <csignal>
#include <memory>
#include <string>
#include <sstream>
#include <os/UnixCurrentThread.h>
#include <iostream>
#include "os/UnixPidFile.h"
#include "function/health/MarsProcessHealth.h"

using namespace function::health;

MarsProcessHealth::MarsProcessHealth(const std::string& pid_file) {
    pidFileObject = std::make_shared<OS::UnixPidFile>();
    processPidFile = pid_file;
}

void MarsProcessHealth::handle(struct evhttp_request *request,
                               const std::shared_ptr<function::http::MarsHttpResponse> &response) {

    response->header("Content-Type", "application/json;charset=utf-8");
    int ret = access(processPidFile.c_str(), F_OK);
    if (ret != 0) {
        response->response(200, "{\"status\":\"DOWN\"}");
        return;
    }

    int fd = pidFileObject->open(processPidFile, O_RDONLY);
    pid_t processId = pidFileObject->getPid();
    ret = kill(processId, 0);
    pidFileObject->closeFd(fd);
    if (ret == 0) {
        response->response(200, "{\"status\":\"UP\"}");
    } else {
        response->response(200, "{\"status\":\"DOWN\"}");
    }
}
