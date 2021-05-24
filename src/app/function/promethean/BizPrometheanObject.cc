//
// Created by zhanglei on 2021/5/22.
//
#include <string>
#include <iostream>
#include <cstdio>
#include <map>

#include "promethean/BizPrometheanObject.h"

using namespace function;

void promethean::BizPrometheanObject::parser(const std::string& content) {
    char bizData[content.length()];
    sscanf(content.c_str(), "[RIG:BIZ]=%s\n", bizData);
    Json::Value prometheanJsonObject;
    jsonParser->jsonDecode(bizData, &prometheanJsonObject);
    std::cout << prometheanJsonObject << std::endl;
    //名字必须存在
    if (!prometheanJsonObject["name"]) {
        std::cout << "name empty" << std::endl;
        return;
    }

    //不是字符串不处理
    if (!prometheanJsonObject["name"].isString()) {
        std::cout << "name is not string" << std::endl;
        return;
    }

    std::string name = prometheanJsonObject["name"].as<std::string>();

    //名字不能是空的
    if (name.empty()) {
        std::cout << "name empty" << std::endl;
        return;
    }

    //类型不能是空
    if (!prometheanJsonObject["type"]) {
        std::cout << "type empty" << std::endl;
        return;
    }

    //不是字符串不处理
    if (!prometheanJsonObject["type"].isString()) {
        std::cout << "type is not string" << std::endl;
        return;
    }

    std::string type = prometheanJsonObject["type"].as<std::string>();

    //获取type对象
    if (type.empty()) {
        std::cout << "type empty" << std::endl;
        return;
    }

    //获取添加值
    if (prometheanJsonObject["val"].empty()) {
        std::cout << "value empty 1" << std::endl;
        return;
    }

    double value = 0;

    if (prometheanJsonObject["val"].isDouble() || prometheanJsonObject["val"].isInt()) {
        //获取添加值
        value = prometheanJsonObject["val"].as<double>();
    }

    //标签信息
    Json::Value tags = prometheanJsonObject["tag"];

    //标签集合必须是对象
    if (!tags.isObject()) {
        std::cout << "tag is not object" << std::endl;
        return;
    }

    //整理标签结果
    if (tags.empty()) {
        std::cout << "tag empty 1" << std::endl;
        return;
    }

    //解析协议
    try {
        //检查标签
        std::map<std::string, std::string> labels;
        Json::Value::Members member = tags.getMemberNames();
        for(auto iter = member.begin(); iter != member.end(); ++iter)
        {
            auto memberValue = tags[*iter];
            if (memberValue.empty()) {
                continue;
            }

            if (!memberValue.isString() && !memberValue.isInt() && !memberValue.isDouble()) {
                continue;
            }

            labels[*iter] = memberValue.asString();
        }
        if (labels.empty()) {
            return;
        }

        //标签信息
        Json::Value config = prometheanJsonObject["config"];
        dispatch(name, type, labels, value, config);
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        return;
    }
}

void promethean::BizPrometheanObject::loadSummaryConfig(std::vector<prometheus::detail::CKMSQuantiles::Quantile>& quantile,
                                                        const Json::Value& config) {
    if (config.empty()) {
        return;
    }

    if (!config.isObject()) {
        return;
    }

    Json::Value percentile = config["percentile"];
    if (percentile.empty()) {
        return;
    }

    if (!percentile.isString() && !percentile.isInt() && !percentile.isDouble()) {
        return;
    }

    std::string percentileString = config["percentile"].asString();
    if (percentileString.empty()) {
        return;
    }

    //按照逗号切割，成为数组
    std::vector<std::string> percentileVector = stringParser.split(percentileString, ",");
    if (percentileVector.empty()) {
        return;
    }

    auto iter = percentileVector.begin();
    for(; iter != percentileVector.end(); iter++) {
        double value = static_cast<double >(atof(iter->c_str()));
        if (value > 0) {
            prometheus::detail::CKMSQuantiles::Quantile data = {value, 0.001};
            quantile.push_back(data);
        }
    }
}

void promethean::BizPrometheanObject::loadHistogramConfig(std::vector<double>& histogramBucket,
                         const Json::Value& config) {
    if (config.empty()) {
        return;
    }

    if (!config.isObject()) {
        return;
    }

    Json::Value bucket = config["sla"];
    if (bucket.empty()) {
        return;
    }

    if (bucket.empty()) {
        return;
    }

    if (!bucket.isString() && !bucket.isInt() && !bucket.isDouble()) {
        return;
    }

    std::string bucketString = config["sla"].asString();
    if (bucketString.empty()) {
        return;
    }

    //按照逗号切割，成为数组
    std::vector<std::string> bucketVector = stringParser.split(bucketString, ",");
    if (bucketVector.empty()) {
        return;
    }

    auto iter = bucketVector.begin();
    for(; iter != bucketVector.end(); iter++) {
        double value = static_cast<double >(atof(iter->c_str()));
        std::cout << value << std::endl;
        if (value > 0) {
            histogramBucket.push_back(value);
        }
    }
}

void promethean::BizPrometheanObject::dispatch(
        const std::string& name,
        const std::string& type,
        const std::map<std::string, std::string>& labels,
        double value,
        const Json::Value& config) {
    if (type == "count") {
        auto& packCounter = prometheanObject->regCountPacket(name);
        auto& biz_counter = packCounter.Add(labels);
        biz_counter.Increment(value);
        return;
    }

    if (type == "gauge") {
        auto& packCounter = prometheanObject->regGaugePacket(name);
        auto& biz_counter = packCounter.Add(labels);
        biz_counter.Increment(value);
        return;
    }

    if (type == "summary") {
        auto& summary_family = prometheanObject->regSummaryPacket(name);
        std::vector<prometheus::detail::CKMSQuantiles::Quantile> quantileConfig;
        quantileConfig = prometheus::Summary::Quantiles{};
        loadSummaryConfig(quantileConfig, config);
        auto& summary = summary_family.Add(labels, quantileConfig);
        summary.Observe(value);
        return;
    }

    if (type == "histogram") {
        auto& packCounter = prometheanObject->regHistogramPacket(name);
        prometheus::Histogram::BucketBoundaries bucketConfig = {};
        loadHistogramConfig(bucketConfig, config);
        auto& biz_counter = packCounter.Add(labels, bucketConfig);
        biz_counter.Observe(value);
        return;
    }

    throw std::range_error("invalid type argument");
}