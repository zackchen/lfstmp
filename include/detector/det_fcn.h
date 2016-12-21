#ifndef _dgfacesdk_detector_fcn_h_
#define _dgfacesdk_detector_fcn_h_
#include <detector.h>
#include <caffe/caffe.hpp>

#include "FaceDetector.h"
namespace DGFace{

class FcnDetector : public Detector {
    public:
        FcnDetector(int img_scale_max, int img_scale_min, const std::string& model_dir, 
					int gpu_id, bool is_encrypt, int batch_size);
        virtual ~FcnDetector(void);
        // detect only -> confidence, bbox
        void detect_impl(const std::vector<cv::Mat> &imgs, std::vector<DetectResult> &results);
    private:

		void ParseConfigFile(std::string cfg_file, std::string& deploy_file, std::string& model_file);

        FCNFaceDetector* _fcn_detecror;
        FacePara _param;
		int _min_det_face_size;
		int _max_det_face_size;
		float _min_scale_face_to_img;
        
};
}
#endif
