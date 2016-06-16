//
// Created by jiajaichen on 16-6-15.
//

#ifndef PROJECT_STORAGE_REQUEST_H
#define PROJECT_STORAGE_REQUEST_H
#include "model/spring.grpc.pb.h"
#include "model/localcommon.pb.h"
#include "witness_bucket.h"
using ::dg::model::SpringService;
using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientAsyncResponseReader;
using grpc::Status;
using grpc::CompletionQueue;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
namespace dg {
class StorageRequest {
public:
    StorageRequest(const Config *config) {

    }
    MatrixError storage() {
        unique_lock<mutex> lock(WitnessBucket::Instance().mt_pop);
        MatrixError err;
        shared_ptr<VehicleObj> v = WitnessBucket::Instance().Pop();
        string storageAddress = v->storageinfo().address();
        shared_ptr<grpc::Channel> channel = grpc::CreateChannel(storageAddress,
                                                                grpc::InsecureChannelCredentials());
        std::unique_ptr<SpringService::Stub> stub_(SpringService::NewStub(channel));
        NullMessage reply;
        ClientContext context;
        CompletionQueue cq;
        Status status;
        std::unique_ptr<ClientAsyncResponseReader<NullMessage> > rpc(
            stub_->AsyncIndexVehicle(&context, *v.get(), &cq));
        rpc->Finish(&reply, &status, (void *) 1);
        void *got_tag;
        bool ok = false;
        cq.Next(&got_tag, &ok);
        if (status.ok()) {
            VLOG(VLOG_SERVICE) << "send to storage success" << endl;
            lock.unlock();
            return err;
        } else {
            VLOG(VLOG_SERVICE) << "send to storage failed" << endl;
            lock.unlock();
            return err;
        }
    }
    ~StorageRequest() { }
private:

};
}
#endif //PROJECT_STORAGE_REQUEST_H