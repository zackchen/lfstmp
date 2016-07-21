/*============================================================================
 * File Name   : ranker_restful.h
 * Author      : yanlongtan@deepglint.com
 * Version     : 1.0.0.0
 * Copyright   : Copyright 2016 DeepGlint Inc.
 * Created on  : 04/15/2016
 * Description : 
 * ==========================================================================*/

#ifndef MATRIX_APPS_RESTFUL_RANKER_H_
#define MATRIX_APPS_RESTFUL_RANKER_H_
#include "restful.h"
#include "services/ranker_service.h"
#include "services/system_service.h"

namespace dg {


typedef MatrixError (*RankFunc)(RankerAppsService *, const FeatureRankingRequest *, FeatureRankingResponse *);

class RestRankerServiceImpl final: public RestfulService<RankerAppsService,RankEngine> {

public:

    RestRankerServiceImpl(Config config,
                          string addr,
                          ServicePool <RankerAppsService,RankEngine> *service_pool)
        : RestfulService(service_pool, config) {
    }

    virtual ~RestRankerServiceImpl() { }

    void Bind(HttpServer &server) {

        RankFunc rank_func = (RankFunc) &RankerAppsService::GetRankedVector;
        bindFunc<RankerAppsService, FeatureRankingRequest, FeatureRankingResponse>(server,
                                                                                   "^/rank$",
                                                                                   "POST",
                                                                                   rank_func);

    }


private:
};

}

#endif //MATRIX_APPS_RESTFUL_RANKER_H_
