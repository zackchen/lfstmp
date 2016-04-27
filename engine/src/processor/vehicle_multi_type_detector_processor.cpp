#include "vehicle_multi_type_detector_processor.h"

namespace dg {
VehicleMultiTypeDetectorProcessor::VehicleMultiTypeDetectorProcessor(
        int batch_size, int gpu_id, int rescale, bool is_model_encrypt)
        : Processor() {

    CaffeConfig config;
    config.batch_size = batch_size;
    config.is_model_encrypt = is_model_encrypt;

    if (config.is_model_encrypt) {
        config.model_file = MODEL_FILE;
        config.deploy_file = DEPLOY_FILE;
    } else {
        config.model_file = MODEL_FILE_EN;
        config.deploy_file = DEPLOY_FILE_EN;
    }

    config.use_gpu = true;
    config.gpu_id = gpu_id;
    config.rescale = rescale;
    detector_ = new VehicleMultiTypeDetector(config);
}

VehicleMultiTypeDetectorProcessor::~VehicleMultiTypeDetectorProcessor() {

}

void VehicleMultiTypeDetectorProcessor::Update(Frame *frame) {

    if (!checkOperation(frame)) {
        LOG(WARNING)<< "OPERATION_VEHICLE_DETECT disable, OPERATION_VEHICLE_TRACK | OPERATION_VEHICLE_STYLE OPERATION_VEHICLE_COLOR | OPERATION_VEHICLE_MARKER OPERATION_VEHICLE_FEATURE_VECTOR also be disabled." << endl;
        return Proceed(frame);
    }

    DLOG(INFO)<< "Start detect frame: " << frame->id() << endl;

    Mat data = frame->payload()->data();
    vector<Detection> detections = detector_->Detect(data);

    for (vector<Detection>::iterator itr = detections.begin();
            itr != detections.end(); ++itr) {
        Detection detection = *itr;
        Object *obj;
        if (1) {
            Vehicle *v = new Vehicle(OBJECT_CAR);
            obj = static_cast<Object*>(v);
            Mat roi = Mat(data, detection.box);
            v->set_image(roi);
        }

        obj->set_detection(detection);
        frame->put_object(obj);
    }
    DLOG(INFO) << "End detector frame" << endl;
    Proceed(frame);

}

void VehicleMultiTypeDetectorProcessor::Update(FrameBatch *frameBatch) {

}

bool VehicleMultiTypeDetectorProcessor::checkOperation(Frame *frame) {
    // if detection disabled, lots of features must be disabled either.
    if (!frame->operation().Check(OPERATION_VEHICLE_DETECT)) {
        frame->operation().Set(
                !(OPERATION_VEHICLE_TRACK | OPERATION_VEHICLE_STYLE
                        | OPERATION_VEHICLE_COLOR | OPERATION_VEHICLE_MARKER
                        | OPERATION_VEHICLE_FEATURE_VECTOR));
        return false;
    }
    return true;
}
bool VehicleMultiTypeDetectorProcessor::checkStatus(Frame *frame) {
    return true;
}
}