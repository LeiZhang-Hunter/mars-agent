//
// Created by zhanglei on 2021/4/16.
//
#include <memory>
#include <functional>
#include "NodeAgent.h"
#include "os/UnixTimer.h"
#include "os/UnixThread.h"
#include "os/UnixCurrentThread.h"
#include "os/UnixThreadContainer.h"
#include "promethean/MarsPrometheanConfig.h"
#include "promethean/MarsPromethean.h"
#include "promethean/MarsPrometheanClient.h"
#include "promethean/MarsPrometheanServer.h"
#include "promethean/MarsPrometheanObject.h"
#include "promethean/BizPrometheanObject.h"
#include "promethean/MarsHttpStandardPrometheanObject.h"

using namespace function;
using namespace std::placeholders;

promethean::MarsPrometheanServer::MarsPrometheanServer(const std::shared_ptr<OS::UnixThreadContainer> &container_,
                                                       const std::shared_ptr<MarsPrometheanConfig> &config_,
                                                       const std::shared_ptr<skywalking::MarsSkyWalking>& apmServer_,
                                                       const std::shared_ptr<MarsPrometheanObject>& promethean_)
                                                       : apmServer(apmServer_), container(container_), config(config_),
                                                       promethean(promethean_){
    bizParser = std::make_shared<BizPrometheanObject>(promethean);
    httpParser = std::make_shared<MarsHttpStandardPrometheanObject>(promethean);
}

void promethean::MarsPrometheanServer::startTimingWheel() {
    auto threadPool = container->getThreadPool();
    size_t len = container->getThreadPool().size();

    //创建时间轮
    for (size_t i = 0; i < len; i++) {
        OS::UnixTimer timer;
        int timerFd = timer.createTimer();
        if (timerFd == -1) {
            std::cerr << "timer:" << timerFd << " create failed;" << std::endl;
            return;
        }
        std::cerr << "timer:" << timerFd << " create success;" << std::endl;
        //获取检查的时间
        timer.setInterval(config->getCheckInterval());
        //循环线程池子
        auto timingWheelChannel = std::make_shared<Event::Channel>(threadPool[i]->getEventLoop(), timerFd);
        size_t wheelCapacity = config->getIdleTime() / config->getCheckInterval();
        std::cerr << "wheelCapacity:" << wheelCapacity << std::endl;
        wheelMap[threadPool[i]->getTid()] = std::make_shared<Event::TimingWheel>(wheelCapacity);
        wheelMap[threadPool[i]->getTid()]->move();
        std::cerr << "bindTid:" << threadPool[i]->getTid() << std::endl;
        timingWheelChannel->setOnReadCallable(std::bind(&MarsPrometheanServer::onIdle, shared_from_this(), _1, _2));
        timingWheelChannel->enableReading(-1);
    }
}

void
promethean::MarsPrometheanServer::prometheanCbListener(struct evconnlistener *listener, int fd, struct sockaddr *addr,
                                                       int len, void *ptr) {
    //创建一个管道，随机绑定
    auto *promethean = (promethean::MarsPromethean *) ptr;
    auto server = promethean->getUnixServer();
    std::shared_ptr<OS::UnixThread> thread = promethean->getNodeAgent()->getUnixThreadContainer()->getRandThread();

    //绑定线程
    thread->addTask(std::bind(&MarsPrometheanServer::bindClient, server, fd, promethean, thread));
}

void promethean::MarsPrometheanServer::bindClient(int fd,
        promethean::MarsPromethean *promethean,
        const std::shared_ptr<OS::UnixThread>& thread) {
    std::shared_ptr<Event::Channel> channel = std::make_shared<Event::Channel>(thread->getEventLoop(), fd);
    //创建一个unix客户端
//    MarsPrometheanClient(int fd, const std::shared_ptr<MarsPrometheanObject> &object,
//    const std::shared_ptr<MarsPrometheanConfig> &config,
//    const std::shared_ptr<MarsPrometheanConfig> &apmServer_,
//    const std::shared_ptr<BizPrometheanObject>& bizParser_,
//    const std::shared_ptr<MarsHttpStandardPrometheanObject>& httpParser_);
    std::shared_ptr<MarsPrometheanClient> prometheanClient =
            std::make_shared<MarsPrometheanClient>
            (fd,
             promethean->getPrometheanObject(),
             promethean->getConfig(),
             apmServer,
             bizParser,
             httpParser);
    channel->setOnReadCallable((std::bind(&MarsPrometheanClient::onRead, prometheanClient, _1, _2)));
    channel->setOnCloseCallable((std::bind(&MarsPrometheanClient::onClose, prometheanClient, _1, _2)));
    //加入到时间轮
    auto iter = this->wheelMap.find(thread->getTid());
    if (iter != this->wheelMap.end()) {
        prometheanClient->setWheelPtr(iter->second);
    }
    //派发事件
    channel->enableReading(-1);
}

void promethean::MarsPrometheanServer::onIdle(struct bufferevent *bev, Event::Channel *channel) {
    auto iter = wheelMap.find(OS::UnixCurrentThread::tid());
    //没找到时间轮
    if (iter == wheelMap.end()) {
        std::cerr << "timing wheel not found" << std::endl;
        return;
    }
    iter->second->move();
}

promethean::MarsPrometheanServer::~MarsPrometheanServer() {
    auto wheelIter = wheelMap.cbegin();
    for (; wheelIter != wheelMap.cend(); wheelIter++) {
        ::close(wheelIter->first);
    }
}