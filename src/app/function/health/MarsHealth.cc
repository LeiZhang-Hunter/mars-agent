//
// Created by zhanglei on 2021/4/26.
//
#include "NodeAgent.h"
#include "function/health/MarsHealth.h"
#include "function/http/MarsHttp.h"
#include "function/http/MarsHttpRouter.h"
#include "module/MarsCoreModule.h"

using namespace function::health;

MarsHealth::MarsHealth(const std::shared_ptr<app::NodeAgent> &agent) {
    router = agent->getCoreModule()->getHttpObject()->getRouter();
    agent->getMarsConfig();
}

void MarsHealth::initFunction() {

}

void MarsHealth::shutdownFunction() {

}

MarsHealth::~MarsHealth() {

}