#include "witness_engine.h"
#include "processor/vehicle_multi_type_detector_processor.h"
#include "processor/vehicle_classifier_processor.h"
#include "processor/vehicle_color_processor.h"
#include "processor/vehicle_marker_classifier_processor.h"
#include "processor/vehicle_belt_classifier_processor.h"

#include "processor/vehicle_plate_recognizer_processor.h"
#include "processor/car_feature_extract_processor.h"
#include "processor/face_detect_processor.h"
#include "processor/face_feature_extract_processor.h"
#include "processor/vehicle_window_detector_processor.h"
#include "processor/config_filter.h"

namespace dg {

WitnessEngine::WitnessEngine(const Config &config) {
    vehicle_processor_ = NULL;
    face_processor_ = NULL;
    is_init_ = false;
    init(config);

}

WitnessEngine::~WitnessEngine() {
    is_init_ = false;

    if (vehicle_processor_) {
        Processor *next = vehicle_processor_;
        Processor *to_delete = next;
        do {
            to_delete = next;
            next = next->GetNextProcessor();
            delete to_delete;
            to_delete = NULL;
        } while (next);
    }

    if (face_processor_) {
        Processor *next = face_processor_;
        Processor *to_delete = next;
        do {
            to_delete = next;
            next = next->GetNextProcessor();
            delete to_delete;
            to_delete = NULL;
        } while (next);
    }
}

void WitnessEngine::Process(FrameBatch *frames) {
    float costtime, diff;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    performance_ += frames->frames().size();
#if DEBUG
#else
    if (performance_ > RECORD_UNIT) {
        if (!RecordPerformance(FEATURE_RESERVED,  performance_)) {
            return;
        }
    }
#endif
    VLOG(VLOG_RUNTIME_DEBUG) << "Start witness engine process" << endl;
    if (frames->CheckFrameBatchOperation(OPERATION_VEHICLE)) {

        if (!enable_vehicle_detect_
                || !frames->CheckFrameBatchOperation(OPERATION_VEHICLE_DETECT)) {
            if (frames->CheckFrameBatchOperation(OPERATION_PEDESTRIAN_ATTR)) {
                Identification baseid = 0;
                for (auto frame : frames->frames()) {
                    Pedestrian *p = new Pedestrian();
                    Mat tmp = frame->payload()->data();
                    if (tmp.empty()) {
                        LOG(ERROR) << "Mat is empty" << endl;
                        return;
                    }
                    p->set_image(tmp);
                    p->set_id(baseid);
                    baseid++;
                    Object *obj = static_cast<Object *>(p);
                    if (obj) {
                        Detection d;
                        d.box = Rect(0, 0, tmp.cols, tmp.rows);
                        obj->set_detection(d);
                        frame->put_object(obj);
                    }
                }
            }
            else {
                Identification baseid = 0;
                for (auto frame : frames->frames()) {
                    Vehicle *v = new Vehicle(OBJECT_CAR);
                    Mat tmp = frame->payload()->data();
                    if (tmp.empty()) {
                        LOG(ERROR) << "Mat is empty" << endl;
                        return;
                    }
                    v->set_image(tmp);
                    v->set_id(baseid);
                    baseid++;
                    Object *obj = static_cast<Object *>(v);

                    if (obj) {
                        Detection d;
                        d.box = Rect(0, 0, tmp.cols, tmp.rows);
                        obj->set_detection(d);
                        frame->put_object(obj);
                    }
                }
            }
        }
        if (vehicle_processor_) {
            vehicle_processor_->Update(frames);
        }
    }

    if (frames->CheckFrameBatchOperation(OPERATION_FACE)) {
        if (face_processor_)
            face_processor_->Update(frames);
    }
    gettimeofday(&end, NULL);

    diff = ((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec)
           / 1000.f;
    DLOG(INFO) << " [witness engine ]: " << diff;

//    if (!isWarmuped_ && ((!enable_vehicle_) || (!enable_vehicle_detect_))) {
//        vehicle_processor_ = vehicle_processor_->GetNextProcessor();
//        isWarmuped_ = true;
//    }

}

void WitnessEngine::initFeatureOptions(const Config &config) {
    enable_vehicle_ = (bool) config.Value(FEATURE_VEHICLE_ENABLE);
    enable_face_ = (bool) config.Value(FEATURE_FACE_ENABLE);

#if DEBUG
    enable_vehicle_detect_ = (bool) config.Value(
                                 FEATURE_VEHICLE_ENABLE_DETECTION);
    enable_vehicle_type_ = (bool) config.Value(FEATURE_VEHICLE_ENABLE_TYPE);

    enable_vehicle_color_ = (bool) config.Value(FEATURE_VEHICLE_ENABLE_COLOR);
    enable_vehicle_plate_ = (bool) config.Value(FEATURE_VEHICLE_ENABLE_PLATE);
    enable_vehicle_plate_gpu_ = (bool) config.Value(
                                    FEATURE_VEHICLE_ENABLE_GPU_PLATE);

    enable_vehicle_marker_ = (bool) config.Value(FEATURE_VEHICLE_ENABLE_MARKER);
    enable_vehicle_feature_vector_ = (bool) config.Value(
                                         FEATURE_VEHICLE_ENABLE_FEATURE_VECTOR);
    enable_vehicle_pedestrian_attr_ = (bool) config.Value(
                                          FEATURE_VEHICLE_ENABLE_PEDISTRIAN_ATTR);

    enable_face_detect_ = (bool) config.Value(
                              FEATURE_FACE_ENABLE_FEATURE_VECTOR);
    enable_face_feature_vector_ = (bool) config.Value(
                                      FEATURE_FACE_ENABLE_DETECTION);
    enable_vehicle_driver_belt_ = (bool) config.Value(
                                      FEATURE_VEHICLE_ENABLE_DRIVERBELT);
    enable_vehicle_codriver_belt_ = (bool) config.Value(
                                        FEATURE_VEHICLE_ENABLE_CODRIVERBELT);
    enable_vehicle_driver_phone_ = (bool) config.Value(
                                       FEATURE_VEHICLE_ENABLE_PHONE);

#else
    enable_vehicle_detect_ = (bool) config.Value(
                                 FEATURE_VEHICLE_ENABLE_DETECTION) && (CheckFeature(FEATURE_CAR_DETECTION, false) == ERR_FEATURE_ON);
    enable_vehicle_type_ = (bool) config.Value(FEATURE_VEHICLE_ENABLE_TYPE) && (CheckFeature(FEATURE_CAR_STYLE, false) == ERR_FEATURE_ON);

    enable_vehicle_color_ = (bool) config.Value(FEATURE_VEHICLE_ENABLE_COLOR) && (CheckFeature(FEATURE_CAR_COLOR, false) == ERR_FEATURE_ON);
    enable_vehicle_plate_ = (bool) config.Value(FEATURE_VEHICLE_ENABLE_PLATE) && (CheckFeature(FEATURE_CAR_PLATE, false) == ERR_FEATURE_ON);
    enable_vehicle_plate_gpu_ = (bool) config.Value(
                                    FEATURE_VEHICLE_ENABLE_GPU_PLATE) && (CheckFeature(FEATURE_CAR_PLATE, false) == ERR_FEATURE_ON);

    enable_vehicle_marker_ = (bool) config.Value(FEATURE_VEHICLE_ENABLE_MARKER) && (CheckFeature(FEATURE_CAR_MARK, false) == ERR_FEATURE_ON);
    enable_vehicle_feature_vector_ = (bool) config.Value(
                                         FEATURE_VEHICLE_ENABLE_FEATURE_VECTOR) && (CheckFeature(FEATURE_CAR_EXTRACT, false) == ERR_FEATURE_ON);
    enable_vehicle_pedestrian_attr_ = (bool) config.Value(
                                          FEATURE_VEHICLE_ENABLE_PEDISTRIAN_ATTR) && (CheckFeature(FEATURE_CAR_PEDESTRIAN_ATTR, false) == ERR_FEATURE_ON);

    enable_face_detect_ = (bool) config.Value(
                              FEATURE_FACE_ENABLE_FEATURE_VECTOR) && (CheckFeature(FEATURE_FACE_DETECTION, false) == ERR_FEATURE_ON);
    enable_face_feature_vector_ = (bool) config.Value(
                                      FEATURE_FACE_ENABLE_DETECTION) && (CheckFeature(FEATURE_FACE_EXTRACT, false) == ERR_FEATURE_ON);
    enable_vehicle_driver_belt_ = (bool) config.Value(
                                      FEATURE_VEHICLE_ENABLE_DRIVERBELT) && (CheckFeature(FEATURE_CAR_MARK, false) == ERR_FEATURE_ON);
    enable_vehicle_codriver_belt_ = (bool) config.Value(
                                        FEATURE_VEHICLE_ENABLE_CODRIVERBELT) && (CheckFeature(FEATURE_CAR_BEHAVIOR_PHONE, false) == ERR_FEATURE_ON);
    enable_vehicle_driver_phone_ = (bool) config.Value(
                                       FEATURE_VEHICLE_ENABLE_PHONE) && (CheckFeature(FEATURE_CAR_BEHAVIOR_NOBELT, false) == ERR_FEATURE_ON);
#endif

}

void WitnessEngine::recordPerformance() {

}

void WitnessEngine::init(const Config &config) {

    ConfigFilter *configFilter = ConfigFilter::GetInstance();
    if (!configFilter->initDataConfig(config)) {
        LOG(ERROR) << "can not init data config" << endl;
        DLOG(ERROR) << "can not init data config" << endl;
        return;
    }

    initFeatureOptions(config);

    Processor *last = NULL;
    if (enable_vehicle_) {
        LOG(INFO) << "Init vehicle processor pipeline. " << endl;

        LOG(INFO) << "Enable accelerate detection processor." << endl;

        VehicleCaffeDetectorConfig dConfig;
        configFilter->createAccelerateConfig(config, dConfig);

        Processor *p = new VehicleMultiTypeDetectorProcessor(dConfig);

        if (last == NULL) {
            vehicle_processor_ = p;
        } else {
            last->SetNextProcessor(p);
        }

        last = p;

        if (enable_vehicle_detect_) {
            LOG(INFO) << "Enable  detection processor." << endl;

            VehicleCaffeDetectorConfig dConfig;
            configFilter->createVehicleCaffeDetectorConfig(config, dConfig);
            Processor *p = new VehicleMultiTypeDetectorProcessor(dConfig);
            if (last == NULL) {
                vehicle_processor_ = p;
            } else {
                last->SetNextProcessor(p);
            }
            last = p;
        }

        if (enable_vehicle_plate_gpu_) {
            LOG(INFO) << "Enable plate detection processor." << endl;

            PlateRecognizeMxnetProcessor::PlateRecognizeMxnetConfig pConfig;
            configFilter->createPlateMxnetConfig(config, &pConfig);

            Processor *p = new PlateRecognizeMxnetProcessor(&pConfig);
            if (last == NULL) {
                vehicle_processor_ = p;
            }
            else {
                last->SetNextProcessor(p);
            }
            last = p;
        }

        if (enable_vehicle_type_) {
            LOG(INFO) << "Enable vehicle type classification processor." << endl;
            vector<VehicleCaffeClassifier::VehicleCaffeConfig> configs;
            configFilter->createVehicleConfig(config, configs);

            Processor *p = new VehicleClassifierProcessor(configs);
            if (last == NULL) {
                vehicle_processor_ = p;
            }
            else {
                last->SetNextProcessor(p);
            }
            last = p;
        }

        if (enable_vehicle_color_) {
            LOG(INFO) << "Enable vehicle color classification processor." << endl;
            vector<CaffeVehicleColorClassifier::VehicleColorConfig> configs;
            configFilter->createVehicleColorConfig(config, configs);

            Processor *p = new VehicleColorProcessor(configs);
            if (last == NULL) {
                vehicle_processor_ = p;
            }
            else {
                last->SetNextProcessor(p);
            }
            last = p;
        }

        if (enable_vehicle_plate_) {
            LOG(INFO) << "Enable vehicle plate processor." << endl;
            PlateRecognizer::PlateConfig pConfig;
            configFilter->createVehiclePlateConfig(config, pConfig);
            Processor *p = new PlateRecognizerProcessor(pConfig);
            if (last == NULL) {
                vehicle_processor_ = p;
            }
            else {
                last->SetNextProcessor(p);
            }
            last = p;
        }

        if (enable_vehicle_marker_ || enable_vehicle_driver_belt_ || enable_vehicle_codriver_belt_ || enable_vehicle_driver_phone_) {
            LOG(INFO) << "Enable vehicle window processor." << endl;

            Processor *p;
            VehicleCaffeDetectorConfig wConfig;
            configFilter->createWindowConfig(config, wConfig);
            p = new VehicleWindowDetectorProcessor(wConfig);
            if (last == NULL) {
                vehicle_processor_ = p;
            }
            else {
                last->SetNextProcessor(p);
            }
            last = p;
        }
        if (enable_vehicle_marker_) {
            VehicleCaffeDetectorConfig mConfig;

            configFilter->createMarkersConfig(config, mConfig);
#if DEBUG
            p = new VehicleMarkerClassifierProcessor(mConfig, (bool) config.Value(DEBUG_VISUALIZATION));
#else
            p = new VehicleMarkerClassifierProcessor(mConfig, false);
#endif
            if (last == NULL) {
                vehicle_processor_ = p;
            }
            else {
                last->SetNextProcessor(p);
            }
            last = p;
        }
        if (enable_vehicle_driver_belt_) {

            VehicleBeltConfig bConfig;

            configFilter->createDriverBeltConfig(config, bConfig);
            p = new VehicleBeltClassifierProcessor(bConfig);

            if (last == NULL) {
                vehicle_processor_ = p;
            }
            else {
                last->SetNextProcessor(p);
            }
            last = p;
        }
        if (enable_vehicle_codriver_belt_) {

            VehicleBeltConfig bConfig;

            configFilter->createCoDriverBeltConfig(config, bConfig);
            p = new VehicleBeltClassifierProcessor(bConfig);
            if (last == NULL) {
                vehicle_processor_ = p;
            }
            else {
                last->SetNextProcessor(p);
            }
            last = p;
        }
        if (enable_vehicle_driver_phone_) {

            VehicleCaffeDetectorConfig bConfig;

            configFilter->createDriverPhoneConfig(config, bConfig);
            p = new VehiclePhoneClassifierProcessor(bConfig);
            if (last == NULL) {
                vehicle_processor_ = p;
            }
            else {
                last->SetNextProcessor(p);
            }
            last = p;
        }
        if (enable_vehicle_feature_vector_) {
            LOG(INFO) << "Enable vehicle feature vector processor." << endl;
            Processor *p = new CarFeatureExtractProcessor();
            if (last == NULL) {
                vehicle_processor_ = p;
            }
            else {
                last->SetNextProcessor(p);
            }
            last = p;
        }

        if (enable_vehicle_pedestrian_attr_) {
            LOG(INFO) << "Enable vehicle pedestrian attr processor." << endl;
            PedestrianClassifier::PedestrianConfig pConfig;
            configFilter->createPedestrianConfig(config, pConfig);
            Processor *p = new PedestrianClassifierProcessor(pConfig);
            if (last == NULL) {
                vehicle_processor_ = p;
            }
            else {
                last->SetNextProcessor(p);
            }
            last = p;
        }

        LOG(INFO) << "Init vehicle processor pipeline finished. " << endl;
        last->SetNextProcessor(NULL);
    }

    if (enable_face_) {
        LOG(INFO) << "Init face processor pipeline. " << endl;
        //FaceDetector::FaceDetectorConfig fdconfig;
        //configFilter->createFaceDetectorConfig(config, fdconfig);
        //face_processor_ = new FaceDetectProcessor(fdconfig);
        FaceDlibDetector::FaceDetectorConfig fdconfig;
        face_processor_ = new FaceDetectProcessor(fdconfig);

        if (enable_face_feature_vector_) {
            LOG(INFO) << "Enable face feature vector processor." << endl;
            FaceFeatureExtractor::FaceFeatureExtractorConfig feconfig;
            configFilter->createFaceExtractorConfig(config, feconfig);
            face_processor_->SetNextProcessor(new FaceFeatureExtractProcessor(feconfig));
        }

        LOG(INFO) << "Init face processor pipeline finished. " << endl;
    }
    if (!RecordPerformance(FEATURE_RESERVED, performance_)) {
        performance_ = RECORD_UNIT;
    }

    Mat image = Mat::zeros(100, 100, CV_8UC3);
    FrameBatch framebatch(0);
    Frame *frame = new Frame(0, image);
    framebatch.AddFrame(frame);
    this->Process(&framebatch);

    if (vehicle_processor_)
        vehicle_processor_ = vehicle_processor_->GetNextProcessor();

//    initGpuMemory(framebatch);
    this->Process(&framebatch);

    is_init_ = true;

}

void WitnessEngine::initGpuMemory(FrameBatch &batch) {

    Mat image = Mat::zeros(1000, 1000, CV_8UC3);
    Mat smallImage = Mat::zeros(50, 50, CV_8UC3);
    Operation op;
    op.Set(1023);
    for (int i = 0; i < 16; ++i) {
        Frame *frame = new Frame(i, image);
        Vehicle *vehicle = new Vehicle(OBJECT_CAR);
        vehicle->set_id(1);
        vehicle->set_image(smallImage);
        vector<Detection> markers;
        Detection det;
        det.box = cv::Rect(1, 1, 10, 10);
        markers.push_back(det);
        //vehicle->set_markers(markers);
        Pedestrian *pedestrain = new Pedestrian();
        pedestrain->set_image(smallImage);
        pedestrain->set_id(2);
        frame->put_object(vehicle);
        frame->put_object(pedestrain);
        frame->set_operation(op);
        batch.AddFrame(frame);
    }
}

}
