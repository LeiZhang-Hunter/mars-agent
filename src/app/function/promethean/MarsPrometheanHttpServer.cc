//
// Created by zhanglei on 2021/5/8.
//
#include <memory>
#include "http/MarsHttpResponse.h"
#include "promethean/MarsPrometheanHttpServer.h"
using namespace function::promethean;
void MarsPrometheanHttpServer::handle(struct evhttp_request *request,
                                  const std::shared_ptr<function::http::MarsHttpResponse> &response) {
    response->response(HTTP_OK, "ok");
}