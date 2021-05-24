//
// Created by zhanglei on 2021/5/22.
//

#include <iostream>
#include "common/MarsJson.h"
#include "common/MarsStringTool.h"
#include "promethean/MarsPrometheanObject.h"
#include "promethean/MarsHttpStandardPrometheanObject.h"

using namespace function;

promethean::MarsHttpStandardPrometheanObject::MarsHttpStandardPrometheanObject(
        const std::shared_ptr<promethean::MarsPrometheanObject> &object) {
    prometheanObject = object;
    jsonParser = std::make_shared<common::MarsJson>();
    stringParser = std::make_shared<common::MarsStringTool>();
}

bool promethean::MarsHttpStandardPrometheanObject::makeBody(HttpBody &body, const Json::Value& jsonBody) {
    return true;
}

void promethean::MarsHttpStandardPrometheanObject::parser(const std::string &content) {
    HttpBody body;
    Json::Value httpProtocol;

    try {
        jsonParser->jsonDecode(content, &httpProtocol);
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

    if (!makeBody(body, httpProtocol)) {
        return;
    }
}