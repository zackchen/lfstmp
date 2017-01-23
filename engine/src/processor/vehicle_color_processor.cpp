/*
 * vehicle_color_processor.cpp
 *
 *  Created on: Apr 27, 2016
 *      Author: jiajiachen
 */

#include "vehicle_color_processor.h"
#include "algorithm_def.h"

using namespace dgvehicle;
namespace dg {

VehicleColorProcessor::VehicleColorProcessor(bool enable_demo) {

    if (!enable_demo) {
        AlgorithmFactory::GetInstance()->CreateBatchProcessor(AlgorithmProcessorType::c_caffeVehicleColorClassifier, classifiers_);
    } else {
        AlgorithmFactory::GetInstance()->CreateBatchProcessor(AlgorithmProcessorType::c_perfectVehicleColorClassifier, classifiers_);
    }
}

VehicleColorProcessor::~VehicleColorProcessor() {
    for (int i = 0; i < classifiers_.size(); i++) {
        delete classifiers_[i];
    }
    objs_.clear();
    classifiers_.clear();
    images_.clear();
}

bool VehicleColorProcessor::process(FrameBatch *frameBatch) {

    VLOG(VLOG_RUNTIME_DEBUG) << "Start color process: " << frameBatch->id() << endl;

    vector<vector<Prediction> > result;
    for (auto *elem : classifiers_) {
     //   auto tmpPred = elem->ClassifyAutoBatch(images_);
        std::vector<vector<Prediction>> tmpPred;
        elem->BatchProcess(images_, tmpPred);
        vote(tmpPred, result, classifiers_.size());
    }

    //set results
    for (int i = 0; i < objs_.size(); i++) {
        Vehicle *v = (Vehicle *) objs_[i];
        Vehicle::Color color;
        if (result[i].size() < 0) {
            continue;
        }
        Prediction max;//= MaxPrediction(result[i]);
        normalize_color(max, result[i]);
        color.class_id = max.first;
        color.confidence = max.second;
        v->set_color(color);
    }

    VLOG(VLOG_RUNTIME_DEBUG) << "Finish color process: " << frameBatch->id() << endl;
    return true;

}

bool VehicleColorProcessor::beforeUpdate(FrameBatch *frameBatch) {

#if DEBUG
#else
    if (performance_ > RECORD_UNIT) {
        if (!RecordFeaturePerformance()) {
            return false;
        }
    }
#endif
    this->vehiclesResizedMat(frameBatch);
    return true;
}

void VehicleColorProcessor::vehiclesResizedMat(FrameBatch *frameBatch) {

    images_.clear();
    objs_.clear();
    objs_ = frameBatch->CollectObjects(OPERATION_VEHICLE_COLOR);
    vector<Object *>::iterator itr = objs_.begin();
    while (itr != objs_.end()) {

        Object *obj = *itr;

        if (obj->type() == OBJECT_CAR) {

            Vehicle *v = (Vehicle *) obj;

            images_.push_back(v->resized_image());
            ++itr;
        } else {
            itr = objs_.erase(itr);
            DLOG(INFO) << "This is not a type of vehicle: " << obj->id() << endl;
        }
    }
}
bool VehicleColorProcessor::RecordFeaturePerformance() {

    return RecordPerformance(FEATURE_CAR_COLOR, performance_);

}
}

