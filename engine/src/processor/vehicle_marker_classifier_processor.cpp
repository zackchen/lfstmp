/*
 * vehicle_marker_classifier_processor.cpp
 *
 *  Created on: Apr 27, 2016
 *      Author: jiajaichen
 */

#include <alg/classification/marker_caffe_classifier.h>
#include "vehicle_marker_classifier_processor.h"
#include "processor_helper.h"
 #include "string_util.h"

namespace dg {

VehicleMarkerClassifierProcessor::VehicleMarkerClassifierProcessor(
    WindowCaffeDetector::WindowCaffeConfig &wConfig,
    MarkerCaffeClassifier::MarkerConfig &mConfig)
    : Processor() {

    classifier_ = new MarkerCaffeClassifier(mConfig);
    detector_ = new WindowCaffeDetector(wConfig);
    window_target_min_ = wConfig.target_min_size;
    window_target_max_ = wConfig.target_max_size;
    marker_target_min_ = mConfig.target_min_size;
    marker_target_max_ = mConfig.target_max_size;
    isSsd = false;
    color_.push_back(Scalar(15, 115, 190));
    color_.push_back(Scalar(230, 2, 0));
    color_.push_back(Scalar(0, 255, 0));
    color_.push_back(Scalar(2, 0, 230));
    color_.push_back(Scalar(255, 255, 0));
    color_.push_back(Scalar(2, 235, 235));
    color_.push_back(Scalar(235, 2, 235));
    color_.push_back(Scalar(155, 255, 0));
    color_.push_back(Scalar(255, 155, 0));
    color_.push_back(Scalar(2, 215, 2));
    color_.push_back(Scalar(2, 115, 2));

}
VehicleMarkerClassifierProcessor::VehicleMarkerClassifierProcessor(
    VehicleCaffeDetectorConfig &wConfig,
    VehicleCaffeDetectorConfig &mConfig,VehicleBeltConfig &bConfig, bool flag)
    : Processor() {

    ssd_marker_detector_ = new MarkerCaffeSsdDetector(mConfig);
    ssd_window_detector_ = new WindowCaffeSsdDetector(wConfig);
    driver_belt_classifier_ = new CaffeBeltClassifier(bConfig);

    window_target_min_ = wConfig.target_min_size;
    window_target_max_ = wConfig.target_max_size;
    marker_target_min_ = mConfig.target_min_size;
    marker_target_max_ = mConfig.target_max_size;
    isSsd = true;
    isVisualization_ = flag;
    color_.push_back(Scalar(15, 115, 190));
    color_.push_back(Scalar(230, 2, 0));
    color_.push_back(Scalar(0, 255, 0));
    color_.push_back(Scalar(2, 0, 230));
    color_.push_back(Scalar(255, 255, 0));
    color_.push_back(Scalar(2, 235, 235));
    color_.push_back(Scalar(235, 2, 235));
    color_.push_back(Scalar(155, 255, 0));
    color_.push_back(Scalar(255, 155, 0));
    color_.push_back(Scalar(2, 215, 2));
    color_.push_back(Scalar(2, 115, 2));

}
VehicleMarkerClassifierProcessor::~VehicleMarkerClassifierProcessor() {
    if (classifier_)
        delete classifier_;
    if (detector_) {
        delete detector_;
    }
    if (ssd_marker_detector_) {
        delete ssd_marker_detector_;
    }
    if (ssd_window_detector_) {
        delete ssd_window_detector_;
    }
    images_.clear();
    resized_images_.clear();
}

bool VehicleMarkerClassifierProcessor::process(FrameBatch *frameBatch) {

    VLOG(VLOG_RUNTIME_DEBUG) << "Start marker and window processor" << frameBatch->id() << endl;
    VLOG(VLOG_SERVICE) << "Start marker and window processor" << endl;

    float costtime, diff;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    if (isSsd) {
        vector<vector<Detection> > crops;
        vector<vector<Detection> > preds;
        vector<Mat> window_images;
        ssd_window_detector_->DetectBatch(images_, crops);
        gettimeofday(&end, NULL);
        diff = ((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec)
               / 1000.f;
        VLOG(VLOG_PROCESS_COST) << "[Total] window cost: " << diff << "ms" << endl;
        for(auto img:images_){
            Mat window_img;
            resize(img,window_img,Size(256,256));
            window_images.push_back(window_img);
        }
        vector<vector<Prediction> > driver_belt_preds = driver_belt_classifier_->ClassifyAutoBatch(window_images);

        ssd_marker_detector_->DetectBatch(images_, crops, preds);

        int cnt = 0;
        struct timeval  end1;

        gettimeofday(&end1, NULL);
        diff = ((end1.tv_sec - end.tv_sec) * 1000000 + end1.tv_usec - end.tv_usec)
               / 1000.f;
        VLOG(VLOG_PROCESS_COST) << "[Total] marker cost: " << diff << "ms" << endl;
                    LOG(INFO)<<color_.size();

        for (int i = 0; i < crops.size(); i++) {
            if (crops[i].size() <= 0)
                continue;

            Vehicle *v = (Vehicle *) objs_[i];
            vector<Detection> markers_cutborad;
            Mat img(v->image());

            if (isVisualization_) {
                for (int j = 0; j < preds[cnt].size(); j++) {
                    Detection d(preds[cnt][j]);

                    d.box.x = (preds[cnt][j].box.x); // + v->detection().box.x;
                    d.box.y = (preds[cnt][j].box.y); // + v->detection().box.y;
                    d.box.width = preds[cnt][j].box.width;
                    d.box.height = preds[cnt][j].box.height;
                    markers_cutborad.push_back(d);
                    if(d.id>color_.size())
                        continue;
                    rectangle(img, preds[cnt][j].box,color_[d.id]);
                    int midx = d.box.x + d.box.width / 2-4;
                    int midy = d.box.y + d.box.height / 2+4;
                    string id = i2string(d.id);

                    cv::putText(img,id, cv::Point(midx, midy), FONT_HERSHEY_COMPLEX_SMALL, 1,color_[d.id]);
                }
                rectangle(img, crops[i][0].box, color_[0]);
                string name = "marker" + to_string(i) + to_string(img.rows) + ".jpg";
                imwrite(name, img);
            } else {
                for (int j = 0; j < preds[cnt].size(); j++) {
                    Detection d(preds[cnt][j]);

                    d.box.x = (preds[cnt][j].box.x); // + v->detection().box.x;
                    d.box.y = (preds[cnt][j].box.y); // + v->detection().box.y;
                    d.box.width = preds[cnt][j].box.width;
                    d.box.height = preds[cnt][j].box.height;
                    markers_cutborad.push_back(d);
                }
            }
            v->set_markers(markers_cutborad);
            cnt++;

        }
            gettimeofday(&end, NULL);
            diff = ((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec)
                   / 1000.f;
            VLOG(VLOG_PROCESS_COST) << "after cost: " << diff << "ms" << endl;


    } else {

        vector<Detection> crops = detector_->DetectBatch(resized_images_,
                                  images_);
        gettimeofday(&end, NULL);
        diff = ((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec)
               / 1000.f;
        VLOG(VLOG_PROCESS_COST) << "Marker window cost: " << diff << "ms" << endl;

        for (int i = 0; i < objs_.size(); i++) {
            Vehicle *v = (Vehicle *) objs_[i];
            v->set_window(crops[i]);
        }
        gettimeofday(&start, NULL);

        vector<Mat> images;
        for (int i = 0; i < crops.size(); i++) {
            Mat img = images_[i](crops[i].box);
            images.push_back(img);
        }

        vector<vector<Detection> > pred = classifier_->ClassifyAutoBatch(images);
        for (int i = 0; i < pred.size(); i++) {
            Vehicle *v = (Vehicle *) objs_[i];
            vector<Detection> markers_cutborad;
            for (int j = 0; j < pred[i].size(); j++) {
                Detection d(pred[i][j]);

                d.box.x = (crops[i].box.x + pred[i][j].box.x); // + v->detection().box.x;
                d.box.y = (crops[i].box.y + pred[i][j].box.y); // + v->detection().box.y;
                d.box.width = pred[i][j].box.width;
                d.box.height = pred[i][j].box.height;
                markers_cutborad.push_back(d);
            }

            v->set_markers(markers_cutborad);

        }
    }


    gettimeofday(&end, NULL);
    diff = ((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec)
           / 1000.f;
    VLOG(VLOG_PROCESS_COST) << "Mareker cost: " << diff << endl;
    objs_.clear();

    VLOG(VLOG_RUNTIME_DEBUG) << "Finish marker and window processor" << frameBatch->id() << endl;
    return true;
}

bool VehicleMarkerClassifierProcessor::beforeUpdate(FrameBatch *frameBatch) {

#if DEBUG
#else
    if (performance_ > RECORD_UNIT) {
        if (!RecordFeaturePerformance()) {
            return false;
        }
    }
#endif
    objs_.clear();
    resized_images_.clear();
    images_.clear();

    objs_ = frameBatch->CollectObjects(OPERATION_VEHICLE_MARKER);
    vector<Object *>::iterator itr = objs_.begin();
    while (itr != objs_.end()) {
        Object *obj = *itr;

        if (obj->type() == OBJECT_CAR) {

            Vehicle *v = (Vehicle *) obj;

            resized_images_.push_back(v->resized_image());
            images_.push_back(v->image());
            ++itr;
            performance_++;

        } else {
            itr = objs_.erase(itr);
            DLOG(INFO) << "This is not a type of vehicle: " << obj->id() << endl;
        }
    }

    return true;

}

bool VehicleMarkerClassifierProcessor::RecordFeaturePerformance() {

    return RecordPerformance(FEATURE_CAR_MARK, performance_);

}
}
