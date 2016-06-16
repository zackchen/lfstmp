// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: spring.proto

#include "spring.pb.h"
#include "spring.grpc.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/channel_interface.h>
#include <grpc++/impl/codegen/client_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/rpc_service_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/sync_stream.h>
namespace dg {
namespace model {

static const char* SpringService_method_names[] = {
  "/dg.model.SpringService/IndexVehicle",
};

std::unique_ptr< SpringService::Stub> SpringService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  std::unique_ptr< SpringService::Stub> stub(new SpringService::Stub(channel));
  return stub;
}

SpringService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_IndexVehicle_(SpringService_method_names[0], ::grpc::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status SpringService::Stub::IndexVehicle(::grpc::ClientContext* context, const ::dg::model::VehicleObj& request, ::dg::model::NullMessage* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_IndexVehicle_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::dg::model::NullMessage>* SpringService::Stub::AsyncIndexVehicleRaw(::grpc::ClientContext* context, const ::dg::model::VehicleObj& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::dg::model::NullMessage>(channel_.get(), cq, rpcmethod_IndexVehicle_, context, request);
}

SpringService::Service::Service() {
  (void)SpringService_method_names;
  AddMethod(new ::grpc::RpcServiceMethod(
      SpringService_method_names[0],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< SpringService::Service, ::dg::model::VehicleObj, ::dg::model::NullMessage>(
          std::mem_fn(&SpringService::Service::IndexVehicle), this)));
}

SpringService::Service::~Service() {
}

::grpc::Status SpringService::Service::IndexVehicle(::grpc::ServerContext* context, const ::dg::model::VehicleObj* request, ::dg::model::NullMessage* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace dg
}  // namespace model

