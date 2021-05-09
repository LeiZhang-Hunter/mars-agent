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

#include <cstring>
#include "os/UnixThread.h"
#include "os/UnixThreadContainer.h"
#include "event/Channel.h"
#include "event/EventLoop.h"
#include "promethean/MarsPromethean.h"
#include "NodeAgent.h"
#include "config/MarsConfig.h"
#include "module/MarsCoreModule.h"
#include "http/MarsHttpAction.h"
#include "http/MarsHttp.h"
#include "http/MarsHttpRouter.h"
#include "promethean/MarsPrometheanConfig.h"
#include "promethean/MarsPrometheanHttpServer.h"
#include "promethean/MarsPrometheanClient.h"

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
}

void promethean::MarsPromethean::initFunction() {
    if (isInit) {
        return;
    }
    //启动域套接字
    loadUnixServer();
    std::shared_ptr<http::MarsHttpAction> action = std::make_shared<http::MarsHttpAction>();
    std::shared_ptr<MarsPrometheanHttpServer> server = std::make_shared<MarsPrometheanHttpServer>();
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
    evconnlistener_new_bind(nodeAgent->getLoop()->getEventBase(),prometheanCbListener, this
    , LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, 1024, (struct sockaddr *) &gSrcAddr, gSockLen);
    return socket;
}

void promethean::MarsPromethean::prometheanCbListener(struct evconnlistener *listener, evutil_socket_t fd,
                                                      struct sockaddr *addr, int len, void *ptr) {
    struct sockaddr_in* client = (sockaddr_in*)addr ;
    std::cout << "connect new client: " << inet_ntoa(client->sin_addr) << "::"<< ntohs(client->sin_port)<< std::endl;
//创建一个管道，随机绑定
    auto *promethean = (promethean::MarsPromethean*)ptr;
    std::shared_ptr<OS::UnixThread> thread = promethean->getNodeAgent()->getUnixThreadContainer()->getRandThread();
    std::shared_ptr<Event::Channel> channel = std::make_shared<Event::Channel>(thread->getEventLoop(), fd);
    std::shared_ptr<MarsPrometheanClient> prometheanClient = std::make_shared<MarsPrometheanClient>();
    channel->setOnReadCallable(std::move(std::bind(&MarsPrometheanClient::onRead, prometheanClient,
            _1, _2)));
    channel->enableReading(-1);
}

void promethean::MarsPromethean::shutdownFunction() {
}

promethean::MarsPromethean::~MarsPromethean() {

}