/*
 * vehicle_color_processor.h
 *
 *  Created on: Apr 26, 2016
 *      Author: jiajiachen
 */

#ifndef SRC_PROCESSOR_VEHICLE_COLOR_PROCESSOR_H_
#define SRC_PROCESSOR_VEHICLE_COLOR_PROCESSOR_H_

#include "processor/processor.h"
#include "alg/vehicle_caffe_classifier.h"
#include "processor_helper.h"
#include "alg/caffe_vehicle_color_classifier.h"

namespace dg {

class VehicleColorProcessor : public Processor {
 public:
    VehicleColorProcessor(
            const vector<VehicleCaffeClassifier::VehicleCaffeConfig> &configs);
    ~VehicleColorProcessor();

 protected:
    virtual bool process(Frame *frame) {
        return false;
    }
    virtual bool process(FrameBatch *frameBatch);
    virtual bool beforeUpdate(FrameBatch *frameBatch);



    virtual bool RecordFeaturePerformance();

 protected:
    void vehiclesResizedMat(FrameBatch *frameBatch);
 private:

    vector<VehicleCaffeClassifier*> classifiers_;
    CaffeVehicleColorClassifier * classifier_;
    vector<Object *> objs_;
    vector<Mat> images_;

};

}

#endif /* SRC_PROCESSOR_VEHICLE_COLOR_PROCESSOR_H_ */
