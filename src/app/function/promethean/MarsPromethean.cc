//
// Created by zhanglei on 2021/5/8.
//
extern "C" {
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>
#include <arpa/inet.h>
}

#include "os/UnixThread.h"
#include "os/UnixThreadContainer.h"
#include "event/TimingWheel.h"
#include "event/Channel.h"
#include "promethean/MarsPromethean.h"
#include "NodeAgent.h"
#include "config/MarsConfig.h"
#include "module/MarsCoreModule.h"
#include "http/MarsHttpAction.h"
#include "http/MarsHttp.h"
#include "http/MarsHttpRouter.h"
#include "promethean/MarsPrometheanConfig.h"
#include "promethean/MarsPrometheanServer.h"
#include "promethean/MarsPrometheanHttpServer.h"
#include "promethean/MarsPrometheanObject.h"

using namespace function;
using namespace std::placeholders;

promethean::MarsPromethean::MarsPromethean(const std::shared_ptr<app::NodeAgent> &agent) {
    std::shared_ptr<config::MarsConfig> marsConfig = agent->getMarsConfig();
    if (!agent) {
        return;
    }
    router = agent->getCoreModule()->getObject<http::MarsHttp>(HTTP_MODULE_NAME)->getRouter();
    prometheanConfig = std::make_shared<MarsPrometheanConfig>();
    //加载配置
    auto yamPromethean = marsConfig->getYamlCore()[PROMETHEAN_MODULE_NAME];
    if (yamPromethean) {
        prometheanConfig->load(yamPromethean);
    }
    nodeAgent = agent;

    //初始化普罗米修斯对象
    promethean = std::make_shared<MarsPrometheanObject>();
    //启动时间轮算法,平均分配到所有线程上去
    std::shared_ptr<OS::UnixThreadContainer> threadContainer = this->getNodeAgent()->getUnixThreadContainer();
    std::vector<std::shared_ptr<OS::UnixThread>> pool = threadContainer->getThreadPool();
    prometheanServer = std::make_shared<MarsPrometheanServer>(threadContainer, prometheanConfig);
}

void promethean::MarsPromethean::finishFunction() {
    if (isFinish) {
        return;
    }

    //初始化时间轮
    prometheanServer->startTimingWheel();
    //启动域套接字监听
    loadUnixServer();
    isFinish = true;
}

void promethean::MarsPromethean::initFunction() {
    std::shared_ptr<http::MarsHttpAction> action = std::make_shared<http::MarsHttpAction>();
    std::shared_ptr<MarsPrometheanHttpServer> server = std::make_shared<MarsPrometheanHttpServer>(promethean);
    action->setUsers(std::bind(&MarsPrometheanHttpServer::handle, server, _1, _2));
    router->getRequest(prometheanConfig->http_path, action);
    isInit = true;
}

int promethean::MarsPromethean::loadUnixServer() {
    //检查路径是否是空的
    if (prometheanConfig->unix_path.empty()) {
        std::cerr << "promethean unix path empty" << std::endl;
        exit(-1);
    }
    int ret;
    //检查文件是否存在
    if (access(prometheanConfig->unix_path.c_str(), F_OK) == 0) {
        //删除旧的路径
        ret = unlink(prometheanConfig->unix_path.c_str());
        if (ret < 0) {
            std::cout << "unlink err!" << prometheanConfig->unix_path.c_str()
                      << ";error msg:" << strerror(errno) << std::endl;
            exit(-1);
        }
    }
    int socket = ::socket(AF_UNIX, SOCK_DGRAM, 0);
    struct sockaddr_un gSrcAddr = {0};
    memset(&gSrcAddr, 0, sizeof(gSrcAddr));
    gSrcAddr.sun_family = AF_UNIX;
    strncpy(gSrcAddr.sun_path, prometheanConfig->unix_path.c_str(), strlen(prometheanConfig->unix_path.c_str()));
    socklen_t gSockLen = strlen(gSrcAddr.sun_path) + sizeof(gSrcAddr.sun_family);
    //监听server
    evconnlistener_new_bind(nodeAgent->getLoop()->getEventBase(), MarsPrometheanServer::prometheanCbListener, this,
                            LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, 1024, (struct sockaddr *) &gSrcAddr, gSockLen);
    return socket;
}

void promethean::MarsPromethean::shutdownFunction() {
}

promethean::MarsPromethean::~MarsPromethean() {

}