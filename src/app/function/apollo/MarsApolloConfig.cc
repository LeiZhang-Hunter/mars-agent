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

        YAML::Node namespaces;
        try {
            namespaces = node["localNamespaces"];
        } catch (std::exception& err) {
            std::cerr << err.what() << std::endl;
        }

        if (namespaces.size() > 0) {
            for(unsigned index = 0; index < app.size(); index++) {
                std::string appNamespace;
                try {
                    appNamespace = namespaces[index].as<std::string>();
                } catch (std::exception& err) {
                    std::cerr << err.what() << std::endl;
                }

                if (appNamespace.empty()) {
                    continue;
                }

                config.localNamespaces.push_back(std::move(appNamespace));
            }
        }
        appVector.push_back(std::move(config));
    }
}