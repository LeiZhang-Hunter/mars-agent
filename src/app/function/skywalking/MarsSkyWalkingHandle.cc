//
// Created by zhanglei on 2021/6/1.
//
#include <cstdlib>
extern "C" {
#include "common/MarsUuid.h"
}
#include "os/UnixTimer.h"
#include "skywalking/MarsSkyWalkingHandle.h"
#include "skywalking/register/Register.grpc.pb.h"
#include "skywalking/register/InstancePing.grpc.pb.h"

using namespace function;
using grpc::Channel;
using grpc::ChannelArguments;
using grpc::ClientContext;
using grpc::Status;

skywalking::MarsSkyWalkingHandle::MarsSkyWalkingHandle(const std::shared_ptr<MarsSkyWalkingConfig> &config_,
        const std::shared_ptr<OS::UnixThread>& thread_) {
    config = config_;
    char buf[UUID4_LEN];
    uuid4_init();
    uuid4_generate(buf);
    uuid = buf;
    thread = thread_;
}


bool skywalking::MarsSkyWalkingHandle::reg(const std::string& serviceName) {
    ChannelArguments args;
    grpcChannel =  CreateCustomChannel(
            config->getGrpcAddress(), grpc::InsecureChannelCredentials(), args);
    std::unique_ptr<Register::Stub> stub_ = Register::NewStub(grpcChannel);

    grpc::ClientContext regContext;
    ServiceRegisterMapping resp;
    Services services;

    //设置服务的名字
    Service* apmServices = services.add_services();
    apmServices->set_servicename(serviceName);

    //设置语言类型
    KeyStringValuePair pair ;
    pair.set_key("language");
    pair.set_value("c++");


    //添加标签
    auto tags = apmServices->add_tags();
    tags->set_key("language");
    tags->set_value("c++");

    //设置属性
    auto Properties = apmServices->properties();
    auto propertiesPair = apmServices->add_properties();
    propertiesPair->set_key("language");
    propertiesPair->set_value("c++");
    auto status = stub_->doServiceRegister(&regContext, services, &resp);
    auto servicesData = resp.services();
    auto iter = servicesData.begin();

    //获取service的id
    serviceId = 0;
    for (iter; iter != servicesData.end() ; iter++) {
        serviceId = iter->value();
        break;
    }

    if (!serviceId) {
        return false;
    }

    char serviceIdString[25];
    //这里使用sprintf
    sprintf(serviceIdString, "%u", serviceId);
    instanceId = serviceIdString;

    time_t unixTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    //struct tm* ptm = localtime(&tt);
    ServiceInstances instances;
    ServiceInstanceRegisterMapping mapping;
    ClientContext serviceInstanceContext;
    auto instance = instances.add_instances();
    instance->set_serviceid(serviceId);
    instance->set_instanceuuid(uuid);
    instance->set_time(unixTime);

    auto osNamePro = instance->add_properties();
    osNamePro->set_key("os_name");
    //目前仅仅支持linux
    osNamePro->set_value("linux");

    auto hostNamePro = instance->add_properties();
    //获取应用的名字
    char name[65];
    int res = gethostname(name, sizeof(name));
    if (res == -1) {
        std::cerr << "gethostname failed;errno:" << errno << ";msg" << strerror(errno) << std::endl;
        hostNamePro->set_key("host_name");
        hostNamePro->set_value("");
    } else {
        hostNamePro->set_key("host_name");
        hostNamePro->set_value(name);
    }

    auto processOnPro = instance->add_properties();
    processOnPro->set_key("process_no");
    processOnPro->set_value("1");

    auto languagePro = instance->add_properties();
    languagePro->set_key("language");
    languagePro->set_value("c++");

    auto marsVersionPro = instance->add_properties();
    marsVersionPro->set_key("mars_version");
    marsVersionPro->set_value("7.1");


    auto agentVersionPro = instance->add_properties();
    agentVersionPro->set_key("agent_version");
    agentVersionPro->set_value("1.0");

    auto ipPro = instance->add_properties();
    ipPro->set_key("ipv4");
    ipPro->set_value("127.0.0.1");

    auto plugins = instance->add_plugins();
    plugins->set_pluginname("mars");
    plugins->set_pluginversion("0.0.1");

    AgentInstance agentNew;
    AgentInstance* agent = agentNew.New();

    agent->set_agentversion("0.0.1");
    agent->set_appname("mars_agent");

    instance->set_allocated_agentinstance(agent);

    status = stub_->doServiceInstanceRegister(&serviceInstanceContext, instances, &mapping);

    if (!status.ok()) {
        return false;
    }

    regString = (instanceId + "," + uuid);

    //加入定时器，定期检测心跳
    OS::UnixTimer timer;
    int timerFd = timer.createTimer();
    if (timerFd == -1) {
        std::cerr << "timer:" << timerFd << " create failed;" << "skywalking ping error" << std::endl;
        return true;
    }

    timer.setInterval(config->getHeartbeatTime());

    //循环线程池子
    pingChannel = std::make_shared<Event::Channel>(thread->getEventLoop(), timerFd);
    pingChannel->setOnReadCallable(std::bind(&MarsSkyWalkingHandle::ping, shared_from_this()));
    pingChannel->enableReading(-1);
    return true;
}

bool skywalking::MarsSkyWalkingHandle::ping() {
    auto timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    std::unique_ptr<ServiceInstancePing::Stub> stubPing_ = ServiceInstancePing::NewStub(grpcChannel);
    ClientContext pingContext;
    Commands respCommand;
    ServiceInstancePingPkg requestPing;
    requestPing.set_time(timeNow.count());
    requestPing.set_serviceinstanceuuid(uuid);
    requestPing.set_serviceinstanceid(serviceId);
    auto status = stubPing_->doPing(&pingContext, requestPing, &respCommand);
    return status.ok();
}