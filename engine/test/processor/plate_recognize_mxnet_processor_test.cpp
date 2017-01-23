#include <processor/plate_recognize_mxnet_processor.h>
#include "gtest/gtest.h"
#include "frame_batch_helper.h"
#include "vehicle_processor_head.h"
#include "file_reader.h"
#include "algorithm_factory.h"

using namespace std;
using namespace dg;

static FrameBatchHelper *fbhelper;
static VehicleProcessorHead *head;
static PlateRecognizeMxnetProcessor *prmprocessor;
static FileReader *resultReader;
static PlateRecognizeMxnetProcessor::PlateRecognizeMxnetConfig *config;

static void initConfig() {
    dgvehicle::AlgorithmFactory::GetInstance()->Initialize("data/dgvehicle", 0, false);
    config = new PlateRecognizeMxnetProcessor::PlateRecognizeMxnetConfig();

    config->is_model_encrypt = false;
    config->gpuId = 0;
    config->enableLocalProvince = true;
    config->localProvinceText = "\u4eac";
    config->localProvinceConfidence = 0;
    config->modelPath = "data/dgLP/Product";
    config->batchsize = 1;
}

static void init() {
    initConfig();
    prmprocessor = new PlateRecognizeMxnetProcessor(*config);
    resultReader = NULL;
    head = new VehicleProcessorHead();
    fbhelper = new FrameBatchHelper(1);
    head->setNextProcessor(prmprocessor);
    dgvehicle::AlgorithmFactory::GetInstance()->ReleaseUselessModel();
}

static void destory() {
    if (head) {
        delete head;
        head = NULL;
    }
    if (fbhelper) {
        delete fbhelper;
        fbhelper = NULL;
    }
    if (resultReader) {
        delete resultReader;
        resultReader = NULL;
    }
    if (config) {
        delete config;
        config = NULL;
    }
}

static Operation getOperation() {
    Operation op;
    op.Set(OPERATION_VEHICLE |
        OPERATION_VEHICLE_PLATE |
        OPERATION_VEHICLE_TRACK |
        OPERATION_VEHICLE_DETECT);
    return op;
}

TEST(PlateRecognizeMxnetTest, plateRecognizeTest) {
    init();
    fbhelper->setBasePath("data/testimg/plateRecognize/recognize/");
    fbhelper->readImage(getOperation());
    FrameBatch *fb = fbhelper->getFrameBatch();

    resultReader = new FileReader("data/testimg/plateRecognize/recognize/result.txt");
    EXPECT_TRUE(resultReader->is_open());
    resultReader->read(",");

    head->process(fb);

    for (int i = 0; i < fb->batch_size(); ++i) {
        stringstream s;
        s << i;
        vector<string> expectPlate = resultReader->getValue(s.str());
        vector<string> realPlate;

        for (int j = 0; j < fb->frames()[i]->objects().size(); ++j) {
            Object *obj = fb->frames()[i]->objects()[j];
            if (obj->type() == OBJECT_CAR) {
                Vehicle *v = (Vehicle *) obj;
                for (int k = 0; k < v->plates().size(); ++k) {
                    realPlate.push_back(v->plates()[k].plate_num);
                }
            }
        }
        EXPECT_EQ(expectPlate.size(), realPlate.size()) << "i = " << i << endl;
        sort(expectPlate.begin(), expectPlate.end());
        sort(realPlate.begin(), realPlate.end());

        for (int j = 0; j < expectPlate.size(); ++j) {
            EXPECT_EQ(expectPlate[j], realPlate[j]);
        }
    }

    delete fbhelper;
    fbhelper = new FrameBatchHelper(1);
    fbhelper->setBasePath("data/testimg/plateRecognize/recognize/");
    fbhelper->readImage(getOperation());

    for (int i = 0; i < fb->batch_size(); ++i) {
        head->getProcessor()->Update(fb->frames()[i]);
        EXPECT_EQ(0, fb->frames()[i]->objects().size()) << "i = " << i << endl;
    }

    destory();
}

TEST(PlateRecognizeMxnetTest, handleWithNoDectorTest) {
    initConfig();
//    config->imageSH = 1080;//600;
//    config->imageSW = 1920;//400;
//    config->numsPlates = 10;//2;
    prmprocessor = new PlateRecognizeMxnetProcessor(*config);
    fbhelper = new FrameBatchHelper(1);
    fbhelper->setBasePath("data/testimg/plateRecognize/recognize/");
    fbhelper->readImage(getOperation());
    FrameBatch *fb = fbhelper->getFrameBatch();

    resultReader = new FileReader("data/testimg/plateRecognize/recognize/result.txt");
    EXPECT_TRUE(resultReader->is_open());
    resultReader->read(",");

    for (int i = 0; i < fb->batch_size(); ++i) {
        Frame *frame = fb->frames()[i];
        Vehicle *vehicle = new Vehicle(OBJECT_CAR);
        Mat tmp = frame->payload()->data();
        Detection d;
        d.set_box(Rect(0, 0, tmp.cols, tmp.rows));
        vehicle->set_id(i);
        vehicle->set_image(tmp);
        Object *obj = static_cast<Object *>(vehicle);
        frame->put_object(obj);
    }

    prmprocessor->Update(fb);

    for (int i = 0; i < fb->batch_size(); ++i) {
        stringstream s;
        s << i;
        vector<string> expectPlate = resultReader->getValue(s.str());
        vector<string> realPlate;

        if (expectPlate.empty()) {
            continue;
        }

        for (int j = 0; j < fb->frames()[i]->objects().size(); ++j) {
            Object *obj = fb->frames()[i]->objects()[j];
            if (obj->type() == OBJECT_CAR) {
                Vehicle *v = (Vehicle *) obj;
                for (int k = 0; k < v->plates().size(); ++k) {
                    realPlate.push_back(v->plates()[k].plate_num);
                }
            }
        }
        bool found = false;
        for (int j = 0; j < expectPlate.size(); ++j) {
            for (int k = 0; k < realPlate.size(); ++k) {
                if (expectPlate[j] == realPlate[k]) {
                    found = true;
                }
            }
        }
        EXPECT_TRUE(found) << "i = " << i << endl;
    }

    delete prmprocessor;
    destory();
}

TEST(PlateRecognizeMxnetTest, plateColorTest) {
    init();
    fbhelper = new FrameBatchHelper(1);
    fbhelper->setBasePath("data/testimg/plateRecognize/color/");
    fbhelper->readImage(getOperation());
    FrameBatch *fb = fbhelper->getFrameBatch();

    FileReader mapping("data/mapping/plate_color.txt");
    EXPECT_TRUE(mapping.is_open());
    mapping.read("=");

    resultReader = new FileReader("data/testimg/plateRecognize/color/result.txt");
    EXPECT_TRUE(resultReader->is_open());
    resultReader->read(",");

    head->process(fb);

    for (int i = 0; i < fb->batch_size(); ++i) {
        stringstream s;
        s << i;
        vector<string> expectColor = resultReader->getValue(s.str());
        if (expectColor.empty()) {
            continue;
        }
        s.str("");

        Vehicle *obj = (Vehicle *) fb->frames()[i]->objects()[0];
        s << obj->plates()[0].color_id;
        vector<string> realColor = mapping.getValue(s.str());
        EXPECT_EQ(expectColor[0], realColor[0]) << "i = " << i << realColor[0] << " " << expectColor[0] << endl;
    }

    destory();
}
