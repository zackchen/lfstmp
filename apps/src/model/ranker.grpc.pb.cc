// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: ranker.proto

#include "ranker.pb.h"
#include "ranker.grpc.pb.h"

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

static const char* SimilarityService_method_names[] = {
        "/dg.model.SimilarityService/GetRankedVector", };

std::unique_ptr<SimilarityService::Stub> SimilarityService::NewStub(
        const std::shared_ptr<::grpc::ChannelInterface>& channel,
        const ::grpc::StubOptions& options) {
    std::unique_ptr<SimilarityService::Stub> stub(
            new SimilarityService::Stub(channel));
    return stub;
}

SimilarityService::Stub::Stub(
        const std::shared_ptr<::grpc::ChannelInterface>& channel)
        : channel_(channel),
          rpcmethod_GetRankedVector_(SimilarityService_method_names[0],
                                     ::grpc::RpcMethod::NORMAL_RPC, channel) {
}

::grpc::Status SimilarityService::Stub::GetRankedVector(
        ::grpc::ClientContext* context,
        const ::dg::model::FeatureRankingRequest& request,
        ::dg::model::FeatureRankingResponse* response) {
    return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_GetRankedVector_,
                                     context, request, response);
}

::grpc::ClientAsyncResponseReader<::dg::model::FeatureRankingResponse>* SimilarityService::Stub::AsyncGetRankedVectorRaw(
        ::grpc::ClientContext* context,
        const ::dg::model::FeatureRankingRequest& request,
        ::grpc::CompletionQueue* cq) {
    return new ::grpc::ClientAsyncResponseReader<
            ::dg::model::FeatureRankingResponse>(channel_.get(), cq,
                                                 rpcmethod_GetRankedVector_,
                                                 context, request);
}

SimilarityService::Service::Service() {
    (void) SimilarityService_method_names;
    AddMethod(
            new ::grpc::RpcServiceMethod(
                    SimilarityService_method_names[0],
                    ::grpc::RpcMethod::NORMAL_RPC,
                    new ::grpc::RpcMethodHandler<SimilarityService::Service,
                            ::dg::model::FeatureRankingRequest,
                            ::dg::model::FeatureRankingResponse>(
                            std::mem_fn(
                                    &SimilarityService::Service::GetRankedVector),
                            this)));
}

SimilarityService::Service::~Service() {
}

::grpc::Status SimilarityService::Service::GetRankedVector(
        ::grpc::ServerContext* context,
        const ::dg::model::FeatureRankingRequest* request,
        ::dg::model::FeatureRankingResponse* response) {
    (void) context;
    (void) request;
    (void) response;
    return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

}  // namespace dg
}  // namespace model

