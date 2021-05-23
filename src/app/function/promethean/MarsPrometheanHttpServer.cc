//
// Created by zhanglei on 2021/5/8.
//
#include <memory>
#include <sstream>

#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>
#include <prometheus/text_serializer.h>
#include <iostream>

#include "common/MarsStringTool.h"
#include "http/MarsHttpResponse.h"
#include "os/UnixCurrentThread.h"
#include "promethean/MarsPrometheanHttpServer.h"
#include "promethean/MarsPrometheanObject.h"
using namespace function::promethean;


MarsPrometheanHttpServer::MarsPrometheanHttpServer(const std::shared_ptr<MarsPrometheanObject>& object)
{
    promethean = object;
}

void MarsPrometheanHttpServer::handle(struct evhttp_request *request,
                                  const std::shared_ptr<function::http::MarsHttpResponse> &response) {
    response->response(HTTP_OK, promethean->serialize());
}