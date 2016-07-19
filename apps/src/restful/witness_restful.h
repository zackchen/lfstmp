/*============================================================================
 * File Name   : witness_restful.h
 * Author      : yanlongtan@deepglint.com
 * Version     : 1.0.0.0
 * Copyright   : Copyright 2016 DeepGlint Inc.
 * Created on  : 04/15/2016
 * Description : 
 * ==========================================================================*/

#ifndef MATRIX_APPS_RESTFUL_WITNESS_H_
#define MATRIX_APPS_RESTFUL_WITNESS_H_

#include "restful.h"
#include "services/witness_service.h"
#include "services/system_service.h"
#include "services/repo_service.h"

namespace dg {

typedef MatrixError (*RecFunc)(WitnessAppsService *, const WitnessRequest *, WitnessResponse *);
typedef MatrixError (*BatchRecFunc)(WitnessAppsService *, const WitnessBatchRequest *, WitnessBatchResponse *);
typedef MatrixError (*RecIndexFunc)(WitnessAppsService *, const IndexRequest *, IndexResponse *);
typedef MatrixError (*RecIndexTxtFunc)(WitnessAppsService *, const IndexTxtRequest *, IndexTxtResponse *);

class RestWitnessServiceImpl final: public RestfulService<WitnessAppsService> {
public:
    RestWitnessServiceImpl(Config config,
                           string addr,
                           MatrixEnginesPool<WitnessAppsService> *engine_pool)
        : RestfulService(engine_pool, config) {

    }

    virtual ~RestWitnessServiceImpl() { }

    void Bind(HttpServer &server) {

        RecFunc rec_func = (RecFunc) &WitnessAppsService::Recognize;
        bindFunc<WitnessAppsService, WitnessRequest, WitnessResponse>(server, "^/rec/image$",
                                                                      "POST", rec_func);
        BatchRecFunc batch_func = (BatchRecFunc) &WitnessAppsService::BatchRecognize;
        bindFunc<WitnessAppsService, WitnessBatchRequest, WitnessBatchResponse>(server,
                                                                                "/rec/image/batch$",
                                                                                "POST",
                                                                                batch_func);

        std::function<MatrixError(const IndexRequest *, IndexResponse *)> indexBinder =
            std::bind(&RepoService::Index, RepoService::GetInstance(), std::placeholders::_1, std::placeholders::_2);
        bindFunc<IndexRequest, IndexResponse>(server, "^/rec/index$", "POST", indexBinder);

        std::function<MatrixError(const IndexTxtRequest *, IndexTxtResponse *)> indexTxtBinder =
            std::bind(&RepoService::IndexTxt, RepoService::GetInstance(), std::placeholders::_1, std::placeholders::_2);
        bindFunc<IndexTxtRequest, IndexTxtResponse>(server, "^/rec/index/txt$", "POST", indexTxtBinder);

    }
    virtual void warmUp(int n) {
        string imgdata =
            "iVBORw0KGgoAAAANSUhEUgAAAAgAAAAICAIAAABLbSncAAAAJElEQVQIHW3BAQEAAAABICb1/5wDqshT5CnyFHmKPEWeIk+RZwAGBKHRhTIcAAAAAElFTkSuQmCC";
        WitnessRequest protobufRequestMessage;
        WitnessResponse protobufResponseMessage;
        protobufRequestMessage.mutable_image()->mutable_data()->set_bindata(imgdata);
        WitnessRequestContext *ctx = protobufRequestMessage.mutable_context();
        ctx->mutable_functions()->Add(1);
        ctx->mutable_functions()->Add(2);
        ctx->mutable_functions()->Add(3);
        ctx->mutable_functions()->Add(4);
        ctx->mutable_functions()->Add(5);
        ctx->mutable_functions()->Add(6);
        ctx->mutable_functions()->Add(7);
        ctx->set_type(REC_TYPE_VEHICLE);
        ctx->mutable_storage()->set_address("127.0.0.1");
        for (int i = 0; i < n; i++) {
            CallData data;
            typedef MatrixError (*RecFunc)(WitnessAppsService *, const WitnessRequest *, WitnessResponse *);
            RecFunc rec_func = (RecFunc) &WitnessAppsService::Recognize;
            data.func = [rec_func, &protobufRequestMessage, &protobufResponseMessage, &data]() -> MatrixError {
              return (bind(rec_func, (WitnessAppsService *) data.apps,
                           placeholders::_1,
                           placeholders::_2))(&protobufRequestMessage,
                                              &protobufResponseMessage);
            };

            if (engine_pool_ == NULL) {
                LOG(ERROR) << "Engine pool not initailized. " << endl;
                return;
            }
            engine_pool_->enqueue(&data);

            MatrixError error = data.Wait();
        }

    }
};
}

#endif //MATRIX_APPS_RESTFUL_WITNESS_H_
