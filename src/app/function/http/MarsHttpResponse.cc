//
// Created by zhanglei on 2021/5/1.
//
extern "C" {
#include "evhttp.h"
}

#include <iostream>
#include "function/http/MarsHttpResponse.h"

using namespace function::http;

MarsHttpResponse::MarsHttpResponse(struct evhttp_request *requestData, const char* uri) {
    request = requestData;
    httpBuffer = evbuffer_new();
    httpUri = uri;
    output_headers = evhttp_request_get_output_headers(request);
}

bool MarsHttpResponse::header(const std::string& key, const std::string& value) {
    evhttp_add_header(request->output_headers, key.c_str(), value.c_str());
    return true;
}

bool MarsHttpResponse::response(short code, const std::string& message) {
    if (!httpBuffer) {
        return false;
    }
    evbuffer_add_printf(httpBuffer, message.c_str(), httpUri);
    evhttp_send_reply(request, code, "", httpBuffer);
    return true;
}

MarsHttpResponse::~MarsHttpResponse() {
    if (!httpBuffer) {
        return;
    }
    evbuffer_free(httpBuffer);
}