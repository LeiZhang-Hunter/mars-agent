//
// Created by zhanglei on 2021/5/22.
//

#ifndef MARS_AGENT_MARSJSON_H
#define MARS_AGENT_MARSJSON_H

#include <string>
#include "json-cpp/json.h"

namespace common {
    class MarsJson {
    public:
        //解码json
        static bool jsonDecode(const std::string& strJsonMess, Json::Value *root);

        //编码json
        static Json::String jsonEncode(const Json::Value& proto_value);
    };
}
#endif //MARS_AGENT_MARSJSON_H
