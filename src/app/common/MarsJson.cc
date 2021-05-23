//
// Created by zhanglei on 2021/5/22.
//

#include "common/MarsJson.h"
using namespace common;
using namespace Json;
bool MarsJson::jsonDecode(const std::string& strJsonMess,Json::Value* root) {
    Json::CharReaderBuilder readerBuilder;
    std::unique_ptr<Json::CharReader>  jsonReader(readerBuilder.newCharReader());
    JSONCPP_STRING errs;
    Json::Value parseValue;
    bool res = jsonReader->parse(strJsonMess.c_str(),strJsonMess.c_str()+strJsonMess.length(),root,&errs);
    if (!res || !errs.empty()) {
        return false;
    }else{
        //转化为map
        return true;
    }
}

//压缩数据
String MarsJson::jsonEncode(Value proto_value){
    StreamWriterBuilder proto_writer;
    //默认不格式化
    proto_writer.settings_["indentation"] = "";
    std::string json_string;
    String serialize_string = writeString(proto_writer,proto_value);
    json_string = serialize_string;
    return json_string;
}

