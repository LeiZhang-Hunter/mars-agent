//
// Created by zhanglei on 2021/5/8.
//
#include <memory>
#include <sstream>
#include "http/MarsHttpResponse.h"
#include "os/UnixCurrentThread.h"
#include "promethean/MarsPrometheanHttpServer.h"
using namespace function::promethean;
void MarsPrometheanHttpServer::handle(struct evhttp_request *request,
                                  const std::shared_ptr<function::http::MarsHttpResponse> &response) {
    std::ostringstream ostr;
    ostr << OS::UnixCurrentThread::tid();
    response->response(HTTP_OK, ostr.str().c_str());
}