//
// Created by chenzhen on 7/6/16.
//

#ifndef PROJECT_SKEYNET_ENGINE_H
#define PROJECT_SKEYNET_ENGINE_H

#include <iostream>
#include <thread>
#include "config.h"
#include "simple_engine.h"
#include "io/stream_tube.h"
#include "io/ringbuffer.h"
#include "vis/display.h"
#include "processor/processor.h"
#include "processor/vehicle_multi_type_detector_processor.h"
#include "processor/parallel/parallel_node.h"
#include "processor/parallel/basic_parallel_processor.h"
#include "algorithm_factory.h"
#include "engine_config_value.h"

using namespace std;
namespace dg {

class SkynetEngine: public SimpleEngine {
public:
    SkynetEngine(const Config &config) {
        init(config);
    }

    void Run() {
        tube_->StartAsyn();
        std::thread t(&SkynetEngine::process, this);
        display_->Run();
        t.join();
    }

    void process() {
        int current = 0;
        BasicParallelProcessor pp(processor_);
        while (true) {
            Frame *f = buffer_->TryNextFrame(current);

            if (f->CheckStatus(FRAME_STATUS_NEW)) {
                cout << "Process next frame: " << f->id() << " " << f->status() << endl;
                pp.Put(f);
                buffer_->NextFrame(current);

            }
//            usleep(30 * 1000);

        }
    }

    void AsynRun() {

    }

private:


    void init(const Config &config) {
        string video = "/home/chenzhen/video/road1.mp4";
        buffer_ = new RingBuffer(100, 640, 480);
        tube_ = new StreamTube(buffer_, video, 25, 1000, 1000, 20000, "TCP");
        display_ = new Displayer(buffer_, "aa", 640, 480, 0, 0, 25);

        int gpu_id = (bool) config.Value(SYSTEM_GPUID);
        bool is_encrypted = (bool) config.Value(DEBUG_MODEL_ENCRYPT);
        bool enable_demo = (bool) config.Value(DEMO_ENABLE);
        string dgvehiclePath = (string) config.Value(DGVEHICLE_MODEL_PATH);
        dgvehicle::AlgorithmFactory::GetInstance()->Initialize(dgvehiclePath, gpu_id, is_encrypted);

//        bool car_only = (bool) config.Value(ADVANCED_DETECTION_CAR_ONLY);
        bool car_only = false;
        processor_ = new VehicleMultiTypeDetectorProcessor(car_only, false, enable_demo);

        dgvehicle::AlgorithmFactory::GetInstance()->ReleaseUselessModel();

    }

    RingBuffer *buffer_;
    StreamTube *tube_;
    Displayer *display_;
    Processor *processor_;

};

}

#endif //PROJECT_SKEYNET_ENGINE_H
