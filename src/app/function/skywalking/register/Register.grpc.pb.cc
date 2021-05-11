// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: register/Register.proto

#include "register/Register.pb.h"
#include "register/Register.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>

static const char* Register_method_names[] = {
  "/Register/doServiceRegister",
  "/Register/doServiceInstanceRegister",
  "/Register/doEndpointRegister",
  "/Register/doNetworkAddressRegister",
  "/Register/doServiceAndNetworkAddressMappingRegister",
};

std::unique_ptr< Register::Stub> Register::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Register::Stub> stub(new Register::Stub(channel));
  return stub;
}

Register::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_doServiceRegister_(Register_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_doServiceInstanceRegister_(Register_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_doEndpointRegister_(Register_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_doNetworkAddressRegister_(Register_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_doServiceAndNetworkAddressMappingRegister_(Register_method_names[4], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Register::Stub::doServiceRegister(::grpc::ClientContext* context, const ::Services& request, ::ServiceRegisterMapping* response) {
  return ::grpc::internal::BlockingUnaryCall< ::Services, ::ServiceRegisterMapping, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_doServiceRegister_, context, request, response);
}

void Register::Stub::experimental_async::doServiceRegister(::grpc::ClientContext* context, const ::Services* request, ::ServiceRegisterMapping* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::Services, ::ServiceRegisterMapping, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doServiceRegister_, context, request, response, std::move(f));
}

void Register::Stub::experimental_async::doServiceRegister(::grpc::ClientContext* context, const ::Services* request, ::ServiceRegisterMapping* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doServiceRegister_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ServiceRegisterMapping>* Register::Stub::PrepareAsyncdoServiceRegisterRaw(::grpc::ClientContext* context, const ::Services& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ServiceRegisterMapping, ::Services, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_doServiceRegister_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ServiceRegisterMapping>* Register::Stub::AsyncdoServiceRegisterRaw(::grpc::ClientContext* context, const ::Services& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdoServiceRegisterRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Register::Stub::doServiceInstanceRegister(::grpc::ClientContext* context, const ::ServiceInstances& request, ::ServiceInstanceRegisterMapping* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ServiceInstances, ::ServiceInstanceRegisterMapping, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_doServiceInstanceRegister_, context, request, response);
}

void Register::Stub::experimental_async::doServiceInstanceRegister(::grpc::ClientContext* context, const ::ServiceInstances* request, ::ServiceInstanceRegisterMapping* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ServiceInstances, ::ServiceInstanceRegisterMapping, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doServiceInstanceRegister_, context, request, response, std::move(f));
}

void Register::Stub::experimental_async::doServiceInstanceRegister(::grpc::ClientContext* context, const ::ServiceInstances* request, ::ServiceInstanceRegisterMapping* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doServiceInstanceRegister_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ServiceInstanceRegisterMapping>* Register::Stub::PrepareAsyncdoServiceInstanceRegisterRaw(::grpc::ClientContext* context, const ::ServiceInstances& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ServiceInstanceRegisterMapping, ::ServiceInstances, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_doServiceInstanceRegister_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ServiceInstanceRegisterMapping>* Register::Stub::AsyncdoServiceInstanceRegisterRaw(::grpc::ClientContext* context, const ::ServiceInstances& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdoServiceInstanceRegisterRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Register::Stub::doEndpointRegister(::grpc::ClientContext* context, const ::Endpoints& request, ::EndpointMapping* response) {
  return ::grpc::internal::BlockingUnaryCall< ::Endpoints, ::EndpointMapping, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_doEndpointRegister_, context, request, response);
}

void Register::Stub::experimental_async::doEndpointRegister(::grpc::ClientContext* context, const ::Endpoints* request, ::EndpointMapping* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::Endpoints, ::EndpointMapping, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doEndpointRegister_, context, request, response, std::move(f));
}

void Register::Stub::experimental_async::doEndpointRegister(::grpc::ClientContext* context, const ::Endpoints* request, ::EndpointMapping* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doEndpointRegister_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::EndpointMapping>* Register::Stub::PrepareAsyncdoEndpointRegisterRaw(::grpc::ClientContext* context, const ::Endpoints& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::EndpointMapping, ::Endpoints, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_doEndpointRegister_, context, request);
}

::grpc::ClientAsyncResponseReader< ::EndpointMapping>* Register::Stub::AsyncdoEndpointRegisterRaw(::grpc::ClientContext* context, const ::Endpoints& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdoEndpointRegisterRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Register::Stub::doNetworkAddressRegister(::grpc::ClientContext* context, const ::NetAddresses& request, ::NetAddressMapping* response) {
  return ::grpc::internal::BlockingUnaryCall< ::NetAddresses, ::NetAddressMapping, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_doNetworkAddressRegister_, context, request, response);
}

void Register::Stub::experimental_async::doNetworkAddressRegister(::grpc::ClientContext* context, const ::NetAddresses* request, ::NetAddressMapping* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::NetAddresses, ::NetAddressMapping, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doNetworkAddressRegister_, context, request, response, std::move(f));
}

void Register::Stub::experimental_async::doNetworkAddressRegister(::grpc::ClientContext* context, const ::NetAddresses* request, ::NetAddressMapping* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doNetworkAddressRegister_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::NetAddressMapping>* Register::Stub::PrepareAsyncdoNetworkAddressRegisterRaw(::grpc::ClientContext* context, const ::NetAddresses& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::NetAddressMapping, ::NetAddresses, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_doNetworkAddressRegister_, context, request);
}

::grpc::ClientAsyncResponseReader< ::NetAddressMapping>* Register::Stub::AsyncdoNetworkAddressRegisterRaw(::grpc::ClientContext* context, const ::NetAddresses& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdoNetworkAddressRegisterRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Register::Stub::doServiceAndNetworkAddressMappingRegister(::grpc::ClientContext* context, const ::ServiceAndNetworkAddressMappings& request, ::Commands* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ServiceAndNetworkAddressMappings, ::Commands, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_doServiceAndNetworkAddressMappingRegister_, context, request, response);
}

void Register::Stub::experimental_async::doServiceAndNetworkAddressMappingRegister(::grpc::ClientContext* context, const ::ServiceAndNetworkAddressMappings* request, ::Commands* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ServiceAndNetworkAddressMappings, ::Commands, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doServiceAndNetworkAddressMappingRegister_, context, request, response, std::move(f));
}

void Register::Stub::experimental_async::doServiceAndNetworkAddressMappingRegister(::grpc::ClientContext* context, const ::ServiceAndNetworkAddressMappings* request, ::Commands* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doServiceAndNetworkAddressMappingRegister_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::Commands>* Register::Stub::PrepareAsyncdoServiceAndNetworkAddressMappingRegisterRaw(::grpc::ClientContext* context, const ::ServiceAndNetworkAddressMappings& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::Commands, ::ServiceAndNetworkAddressMappings, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_doServiceAndNetworkAddressMappingRegister_, context, request);
}

::grpc::ClientAsyncResponseReader< ::Commands>* Register::Stub::AsyncdoServiceAndNetworkAddressMappingRegisterRaw(::grpc::ClientContext* context, const ::ServiceAndNetworkAddressMappings& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdoServiceAndNetworkAddressMappingRegisterRaw(context, request, cq);
  result->StartCall();
  return result;
}

Register::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Register_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Register::Service, ::Services, ::ServiceRegisterMapping, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Register::Service* service,
             ::grpc::ServerContext* ctx,
             const ::Services* req,
             ::ServiceRegisterMapping* resp) {
               return service->doServiceRegister(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Register_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Register::Service, ::ServiceInstances, ::ServiceInstanceRegisterMapping, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Register::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ServiceInstances* req,
             ::ServiceInstanceRegisterMapping* resp) {
               return service->doServiceInstanceRegister(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Register_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Register::Service, ::Endpoints, ::EndpointMapping, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Register::Service* service,
             ::grpc::ServerContext* ctx,
             const ::Endpoints* req,
             ::EndpointMapping* resp) {
               return service->doEndpointRegister(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Register_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Register::Service, ::NetAddresses, ::NetAddressMapping, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Register::Service* service,
             ::grpc::ServerContext* ctx,
             const ::NetAddresses* req,
             ::NetAddressMapping* resp) {
               return service->doNetworkAddressRegister(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Register_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Register::Service, ::ServiceAndNetworkAddressMappings, ::Commands, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Register::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ServiceAndNetworkAddressMappings* req,
             ::Commands* resp) {
               return service->doServiceAndNetworkAddressMappingRegister(ctx, req, resp);
             }, this)));
}

Register::Service::~Service() {
}

::grpc::Status Register::Service::doServiceRegister(::grpc::ServerContext* context, const ::Services* request, ::ServiceRegisterMapping* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Register::Service::doServiceInstanceRegister(::grpc::ServerContext* context, const ::ServiceInstances* request, ::ServiceInstanceRegisterMapping* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Register::Service::doEndpointRegister(::grpc::ServerContext* context, const ::Endpoints* request, ::EndpointMapping* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Register::Service::doNetworkAddressRegister(::grpc::ServerContext* context, const ::NetAddresses* request, ::NetAddressMapping* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Register::Service::doServiceAndNetworkAddressMappingRegister(::grpc::ServerContext* context, const ::ServiceAndNetworkAddressMappings* request, ::Commands* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


