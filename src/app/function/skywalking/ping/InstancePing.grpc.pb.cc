// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: register/InstancePing.proto

#include "register/InstancePing.pb.h"
#include "register/InstancePing.grpc.pb.h"

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

static const char* ServiceInstancePing_method_names[] = {
  "/ServiceInstancePing/doPing",
};

std::unique_ptr< ServiceInstancePing::Stub> ServiceInstancePing::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ServiceInstancePing::Stub> stub(new ServiceInstancePing::Stub(channel));
  return stub;
}

ServiceInstancePing::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_doPing_(ServiceInstancePing_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ServiceInstancePing::Stub::doPing(::grpc::ClientContext* context, const ::ServiceInstancePingPkg& request, ::Commands* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ServiceInstancePingPkg, ::Commands, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_doPing_, context, request, response);
}

void ServiceInstancePing::Stub::experimental_async::doPing(::grpc::ClientContext* context, const ::ServiceInstancePingPkg* request, ::Commands* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ServiceInstancePingPkg, ::Commands, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doPing_, context, request, response, std::move(f));
}

void ServiceInstancePing::Stub::experimental_async::doPing(::grpc::ClientContext* context, const ::ServiceInstancePingPkg* request, ::Commands* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doPing_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::Commands>* ServiceInstancePing::Stub::PrepareAsyncdoPingRaw(::grpc::ClientContext* context, const ::ServiceInstancePingPkg& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::Commands, ::ServiceInstancePingPkg, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_doPing_, context, request);
}

::grpc::ClientAsyncResponseReader< ::Commands>* ServiceInstancePing::Stub::AsyncdoPingRaw(::grpc::ClientContext* context, const ::ServiceInstancePingPkg& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdoPingRaw(context, request, cq);
  result->StartCall();
  return result;
}

ServiceInstancePing::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ServiceInstancePing_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ServiceInstancePing::Service, ::ServiceInstancePingPkg, ::Commands, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ServiceInstancePing::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ServiceInstancePingPkg* req,
             ::Commands* resp) {
               return service->doPing(ctx, req, resp);
             }, this)));
}

ServiceInstancePing::Service::~Service() {
}

::grpc::Status ServiceInstancePing::Service::doPing(::grpc::ServerContext* context, const ::ServiceInstancePingPkg* request, ::Commands* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


