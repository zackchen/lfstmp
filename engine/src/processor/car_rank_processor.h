/*============================================================================
 * File Name   : car_rank_processor.h
 * Author      : yanlongtan@deepglint.com
 * Version     : 1.0.0.0
 * Copyright   : Copyright 2016 DeepGlint Inc.
 * Created on  : 04/15/2016
 * Description :
 * ==========================================================================*/

#ifndef MATRIX_ENGINE_CAR_RANK_PROCESSOR_H_
#define MATRIX_ENGINE_CAR_RANK_PROCESSOR_H_

#include <glog/logging.h>

#include "processor.h"
#include "model/frame.h"
#include "model/rank_feature.h"
//#include "alg/feature/car_matcher.h"
//#include "alg/feature/car_feature_extractor.h"
#include "config.h"
#include "timing_profiler.h"
#include "algorithm_factory.h"

namespace dg {

class CarRankProcessor: public Processor {
public:
    CarRankProcessor();
    virtual ~CarRankProcessor();

protected:
    virtual bool process(Frame *frame);
    virtual bool process(FrameBatch *frameBatch) {
        return false;
    }
    virtual bool beforeUpdate(FrameBatch *frameBatch);


    virtual bool RecordFeaturePerformance();

    virtual string processorName() {
        return "CarRankProcessor";
    }
private:
    dgvehicle::ICarMatcher *car_matcher_ = NULL;
    dgvehicle::ICarFeatureExtractor* car_feature_extractor_ = nullptr;

    vector<Score> rank(const Mat &image, const Rect &hotspot,
                       const vector<CarRankFeature> &candidates);
};

}

#endif //MATRIX_ENGINE_CAR_RANK_PROCESSOR_H_
