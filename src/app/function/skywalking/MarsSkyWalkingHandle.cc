//
// Created by zhanglei on 2021/6/1.
//

#include "skywalking/MarsSkyWalkingHandle.h"
#include "skywalking/register/Register.grpc.pb.h"

using namespace function;
using grpc::Channel;
using grpc::ChannelArguments;
using grpc::ClientContext;
using grpc::Status;


std::string skywalking::MarsSkyWalkingHandle::reg() {
    ChannelArguments args;
    std::shared_ptr<Channel> grpcChannel =  CreateCustomChannel(
            config->getGrpcAddress(), grpc::InsecureChannelCredentials(), args);
    std::unique_ptr<Register::Stub> stub_ = Register::NewStub(grpcChannel);

    grpc::ClientContext regContext;
    ServiceRegisterMapping resp;
    Services services;

    //设置服务的名字
    Service* apmServices = services.add_services();
    apmServices->set_servicename("mars");

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
    unsigned int service_id;
    for (iter; iter != servicesData.end() ; iter++) {
        service_id = iter->value();
        break;
    }

    std::cout << "service_id:" <<service_id << std::endl;
}