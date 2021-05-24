# mars-agent

## 项目背景

由于部门所有业务都迁移到了K8S，需要一个强有力的agent作为支撑，所以打算使用cpp，基于libevent，开发一个高性能
的agent，所以开发这个作品,希望可以用在部门中

为了最大利用多核和cpu，采用纯异步，将会最大限度利用内核态

## 目标集成功能

1.Apollo 携程稳定的配置中心

2.Eureka 服务注册中心，跨语言，任何服务都可以无侵入方式接入

3.健康检查

4.日志收集,直接继承旧的Atel的功能

5.普罗米修斯客户端

6.IPTABLES网络流量监控过滤，由于虎扑linux内核很老，不支持当下最新的伯里克过滤器技术

## 采用的第三方库

1.网路通讯库libevent

下载地址:https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/libevent-2.1.12-stable.tar.gz

2.yaml-cpp

mars使用的配置文件格式是yaml

yaml-cpp的github地址为

https://github.com/jbeder/yaml-cpp

3.grpc
注册 skywalking:

```
#include <iostream>
#include <fstream>
#include <grpcpp/grpcpp.h>
#include "proto/register/Register.grpc.pb.h"

using grpc::Channel;
using grpc::ChannelArguments;
using grpc::ClientContext;
using grpc::Status;

int main(void)
{
    ChannelArguments args;
//    消息封装
    std::shared_ptr<Channel> channel = grpc::CreateCustomChannel(
    "rig-acc-ser-sit.hupu.io:11800", grpc::InsecureChannelCredentials(), args);
    std::unique_ptr<Register::Stub> stub_ = Register::NewStub(channel);
    ClientContext context;
    ServiceRegisterMapping resp;
    Services services;
    Service* s = services.add_services();

    s->set_servicename("test");
    std::cout << s->DebugString() << std::endl;

    KeyStringValuePair pair ;
    pair.set_key("language");
    pair.set_value("php");
    auto tags = s->add_tags();
    tags->set_key("language");
    tags->set_value("php");
    auto Properties = s->properties();
    auto pair2 = s->add_properties();
    pair2->set_key("language");
    pair2->set_value("php");
//    auto mapping = stub_->AsyncdoServiceRegister(&context, services, &cq);
    std::cout << services.DebugString() << std::endl;
    auto status = stub_->doServiceRegister(&context, services, &resp);
    auto servicesData = resp.services();
    auto iter = servicesData.begin();

    unsigned int service_id;
    for (iter; iter != servicesData.end() ; iter++) {
        service_id = iter->value();
    }

    ServiceInstances instances;
    ServiceInstanceRegisterMapping mapping;
    ClientContext context2;
    auto instance = instances.add_instances();
    instance->set_serviceid(service_id);
    instance->set_instanceuuid("dsadsadsadsadada");
    instance->set_time(1111111);
    auto instancePro1 = instance->add_properties();
    instancePro1->set_key("os_name");
    instancePro1->set_value("linux");

    auto instancePro2 = instance->add_properties();
    instancePro2->set_key("host_name");
    instancePro2->set_value("zhanglei");

    auto instancePro3 = instance->add_properties();
    instancePro3->set_key("process_no");
    instancePro3->set_value("1");

    auto instancePro4 = instance->add_properties();
    instancePro4->set_key("language");
    instancePro4->set_value("php");

    auto instancePro5 = instance->add_properties();
    instancePro5->set_key("php_version");
    instancePro5->set_value("7.1");

    auto instancePro6 = instance->add_properties();
    instancePro6->set_key("agent_version");
    instancePro6->set_value("1.0");

    auto instancePro7 = instance->add_properties();
    instancePro7->set_key("ipv4");
    instancePro7->set_value("127.0.0.1");

    auto plugins = instance->add_plugins();
    plugins->set_pluginname("mars");
    plugins->set_pluginversion("0.0.1");

    AgentInstance agent1;
    AgentInstance* agent = agent1.New();

    agent->set_agentversion("0.0.1");
    agent->set_appname("mars_agent");

    instance->set_allocated_agentinstance(agent);

    stub_->doServiceInstanceRegister(&context2, instances, &mapping);

    std::cout << instances.DebugString() << std::endl;

    if (status.ok()) {
        return 0;
    } else {
        return -1;
    }
}
```