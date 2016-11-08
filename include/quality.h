#ifndef _DGFACESDK_QUALITY_H_
#define _DGFACESDK_QUALITY_H_

#include <opencv2/opencv.hpp>
#include "common.h"
#include <alignment.h>

namespace DGFace{
class Quality {
    public:
        virtual ~Quality(void) {}
        virtual float quality(const cv::Mat &image) {}
        virtual std::vector<float> quality(const AlignResult &align_result) {}
    protected:
        Quality(void) {}
};

Quality *create_quality(const std::string &prefix = std::string());
}
#endif
