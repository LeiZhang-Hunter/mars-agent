//
// Created by zhanglei on 2021/6/6.
//

#include <iostream>
#include "apollo/MarsApolloConfig.h"

using namespace function;

void apollo::MarsApolloConfig::load(const YAML::Node& node) {
    try {
        api = node["api"].as<std::string>();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    try {
        server = node["server"].as<std::string>();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }


    try {
        port = node["port"].as<uint16_t>();
        stringPort = node["port"].as<std::string>();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    YAML::Node app;
    try {
        app = node["app"];
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
        return;
    }

    host = (server + ":");
    host += stringPort;

    for(unsigned i=0; i < app.size(); i++) {
        apolloAppConfig config;
        try {
            config.appId = app[i]["appId"].as<std::string>();
        } catch (std::exception& err) {
            std::cerr << err.what() << std::endl;
        }
        if (config.appId.empty())
            continue;

        try {
            config.cluster = app[i]["cluster"].as<std::string>();
        } catch (std::exception& err) {
            std::cerr << err.what() << std::endl;
        }

        try {
            config.env = app[i]["env"].as<std::string>();
        } catch (std::exception& err) {
            std::cerr << err.what() << std::endl;
        }

        if (app[i]["localNamespaces"] && app[i]["localNamespaces"].size() > 0) {
            for(unsigned index = 0; index < app.size(); index++) {
                std::string appNamespace;
                try {
                    appNamespace = app[i]["localNamespaces"][index].as<std::string>();
                } catch (std::exception& err) {
                    std::cerr << err.what() << std::endl;
                }

                if (appNamespace.empty()) {
                    continue;
                }
                std::pair<std::string, int> appPair;
                appPair.first = appNamespace;
                appPair.second = -1;
                config.localNamespaces.push_back(std::move(appPair));
            }
        }
        appVector.push_back(std::move(config));
    }
}