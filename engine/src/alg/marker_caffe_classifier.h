/*
 * marker_caffe_classifier.h
 *
 *  Created on: Apr 21, 2016
 *      Author: jiajaichen
 */

#ifndef SRC_ALG_MARKER_CAFFE_CLASSIFIER_H_
#define SRC_ALG_MARKER_CAFFE_CLASSIFIER_H_
#include <cassert>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <caffe/caffe.hpp>
#include "model/basic.h"
#include "model/model.h"

#include "detector.h"
#include "caffe_config.h"
using namespace std;
using namespace caffe;
using namespace cv;
namespace dg {

class MarkerCaffeClassifier {
 public:
     enum MarkerType {
          MOT = 2,
          Accessories = 1,
          TissueBox = 4,
          Belt = 0,
          Others = 3,
          SunVisor = 5,
          Global = 100
     };
     typedef struct {
          vector<float> area;
          vector<float> ratio;
          Scalar color;
          float stride;
          int id;
          float threshold;
          int max;
          float confidence;
     } Marker;
     typedef struct {
          float accessories_x0 = 0.3;
          float accessories_y0 = 0.7;
          float mot_x0 = 0.23;
          float mot_x1 = 0.4;
          float mot_y0 = 0.38;
          float mot_y1 = 0.85;
          float sunVisor_x0 = 0.4;
          float sunVisor_x1 = 0.6;
          float sunVisor_y0 = 0.25;
          float sunVisor_y1 = 0.6;
          float global_confidence = 0.8;
          map<int, float> marker_confidence;
     } MarkerConfig;
     MarkerCaffeClassifier(CaffeConfig &config, MarkerConfig &markerconfig);
     virtual ~MarkerCaffeClassifier();
     vector<vector<Detection > > ClassifyAutoBatch(vector<Mat> imgs);
 protected:
     vector<vector<Detection > > ClassifyBatch(vector<Mat> imgs);

     vector<vector<Detection> > get_final_bbox(
               vector<Mat> image, Blob<float>* cls, Blob<float>* reg,
               vector<float> enlarge_ratio, Marker &marker,
               vector<Mat> origin_img);
     bool filter(Detection, int row, int col);

     std::vector<Blob<float>*> PredictBatch(vector<Mat> imgs);

 private:
     void setupMarker();
     boost::shared_ptr<caffe::Net<float> > net_;
     int num_channels_;
     cv::Size input_geometry_;
     bool device_setted_;
     CaffeConfig caffe_config_;
     MarkerConfig marker_config_;
     int means_[3];
     int rescale_;
     map<int, Marker> markers_;
};
}
#endif /* SRC_ALG_MARKER_CAFFE_CLASSIFIER_H_ */
