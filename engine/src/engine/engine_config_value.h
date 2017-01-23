/*
 * engine_config_value.h
 *
 *  Created on: Apr 25, 2016
 *      Author: chenzhen
 */

#ifndef ENGINE_CONFIG_VALUE_H_
#define ENGINE_CONFIG_VALUE_H_

#include <string>

using namespace std;

namespace dg {

static const string SYSTEM_GPUID = "System/GpuId";
static const string DGVEHICLE_MODEL_PATH = "ModelPath/dgvehicle";
static const string DGLP_MODEL_PATH = "ModelPath/dgLP";
static const string DGFACE_MODEL_PATH = "ModelPath/dgface";
static const string DEMO_ENABLE = "DemoEnable";

// feature/vehicle
static const string FEATURE_VEHICLE_ENABLE = "Feature/Vehicle/Enable";
static const string FEATURE_VEHICLE_ENABLE_NONMOTORVEHICLE = "Feature/Vehicle/EnableNonMotorVehicle";
static const string FEATURE_VEHICLE_ENABLE_DETECTION = "Feature/Vehicle/EnableDetection";
static const string FEATURE_VEHICLE_ENABLE_TYPE = "Feature/Vehicle/EnableType";
static const string FEATURE_VEHICLE_ENABLE_COLOR = "Feature/Vehicle/EnableColor";
static const string FEATURE_VEHICLE_ENABLE_PLATE = "Feature/Vehicle/EnablePlate";
static const string FEATURE_VEHICLE_ENABLE_PLATE_ENHANCED = "Feature/Vehicle/EnablePlateEnhanced";
static const string FEATURE_VEHICLE_ENABLE_GPU_PLATE = "Feature/Vehicle/EnableGpuPlate";
static const string FEATURE_VEHICLE_ENABLE_MARKER = "Feature/Vehicle/EnableMarker";
static const string FEATURE_VEHICLE_ENABLE_DRIVERBELT = "Feature/Vehicle/EnableDriverBelt";
static const string FEATURE_VEHICLE_ENABLE_CODRIVERBELT = "Feature/Vehicle/EnableCoDriverBelt";
static const string FEATURE_VEHICLE_ENABLE_PHONE = "Feature/Vehicle/EnablePhone";
static const string FEATURE_VEHICLE_ENABLE_FEATURE_VECTOR = "Feature/Vehicle/EnableFeatureVector";
static const string FEATURE_VEHICLE_ENABLE_PEDISTRIAN_ATTR = "Feature/Vehicle/EnablePedestrianAttr";
static const string FEATURE_NON_MOTOR_VEHICLE_ENABLE = "Feature/Vehicle/EnableNonMotorVehicle";
// feature/face
static const string FEATURE_FACE_ENABLE = "Feature/Face/Enable";
static const string FEATURE_FACE_ENABLE_DETECTION =
    "Feature/Face/EnableDetection";
static const string FEATURE_FACE_ENABLE_FEATURE_VECTOR =
    "Feature/Face/EnableFeatureVector";
static const string FEATURE_FACE_ENABLE_QUALITY =
    "Feature/Face/EnableQuality";
static const string FEATURE_FACE_ENABLE_ALIGNMENT =
    "Feature/Face/EnableAlignment";
static const string FEATURE_FACE_ENABLE_POSE =
    "Feature/Face/EnablePose";
static const string RANKER_DEFAULT_TYPE = "RankerType";

static const string DEBUG_MODEL_ENCRYPT = "Debug/Encrypt";
static const string DEBUG_ENABLE = "Debug/Enable";


//static const string ADVANCED_DETECTION_RESCALE = "Advanced/Detection/Rescale";
//static const string ADVANCED_DETECTION_BATCH_SIZE =
//    "Advanced/Detection/BatchSize";
//static const string ADVANCED_DETECTION_TARGET_MIN_SIZE =
//    "Advanced/Detection/TargetMinSize";
//static const string ADVANCED_DETECTION_TARGET_MAX_SIZE =
//    "Advanced/Detection/TargetMaxSize";
//static const string ADVANCED_DETECTION_CAR_ONLY =
//    "Advanced/Detection/CarOnly";
//static const string ADVANCED_DETECTION_THRESHOLD = "Advanced/Detection/Threshold";


//static const string ADVANCED_COLOR_BATCH_SIZE = "Advanced/Color/BatchSize";
//static const string ADVANCED_COLOR_MODEL_NUM = "Advanced/Color/ModelNum";
//
//static const string ADVANCED_STYLE_BATCH_SIZE = "Advanced/Style/BatchSize";
//static const string ADVANCED_STYLE_MODEL_NUM = "Advanced/Style/ModelNum";
//
//static const string ADVANCED_WINDOW_BATCH_SIZE = "Advanced/Window/BatchSize";
//
//static const string ADVANCED_MARKER_BATCH_SIZE = "Advanced/Marker/BatchSize";
//
//static const string ADVANCED_DRIVER_BELT_BATCH_SIZE = "Advanced/DriverBelt/BatchSize";
//static const string ADVANCED_CODRIVER_BELT_BATCH_SIZE = "Advanced/CoDriverBelt/BatchSize";
static const string ADVANCED_DRIVER_BELT_THRESHOLD = "Advanced/DriverBelt/Threshold";
static const string ADVANCED_CODRIVER_BELT_THRESHOLD = "Advanced/CoDriverBelt/Threshold";
//static const string ADVANCED_PHONE_BATCH_SIZE = "Advanced/DriverPhone/BatchSize";
static const string ADVANCED_PHONE_THRESHOLD = "Advanced/DriverPhone/Threshold";

//static const string ADVANCED_MARKER_MOT_CONFIDENCE =
//    "Advanced/Marker/MOTConfidence";
//static const string ADVANCED_MARKER_BETLT_CONFIDENCE =
//    "Advanced/Marker/BeltConfidence";
//static const string ADVANCED_MARKER_GLOBAL_CONFIDENCE =
//    "Advanced/Marker/GlobalConfidence";
//static const string ADVANCED_MARKER_ACCESSORIES_CONFIDENCE =
//    "Advanced/Marker/AccessoriesConfidence";
//static const string ADVANCED_MARKER_OTHERS_CONFIDENCE =
//    "Advanced/Marker/OthersConfidence";
//static const string ADVANCED_MARKER_TISSUEBOX_CONFIDENCE =
//    "Advanced/Marker/TissueBoxConfidence";
//static const string ADVANCED_MARKER_SUNVISOR_CONFIDENCE =
//    "Advanced/Marker/SunVisorConfidence";

static const string ADVANCED_FACE_DETECT_BATCH_SIZE =
    "Advanced/FaceDetect/BatchSize";
static const string ADVANCED_FACE_DETECT_METHOD = "Advanced/FaceDetect/Method";
//static const string ADVANCED_FACE_DETECT_SCALE = "Advanced/FaceDetect/Scale";
//static const string ADVANCED_FACE_DETECT_MIN = "Advanced/FaceDetect/Min";
//static const string ADVANCED_FACE_DETECT_MAX = "Advanced/FaceDetect/Max";

//static const string ADVANCED_FACE_DETECT_CONFIDENCE =
//    "Advanced/FaceDetect/Confidence";

static const string ADVANCED_FACE_EXTRACT_BATCH_SIZE =
    "Advanced/FaceExtract/BatchSize";
//static const string ADVANCED_FACE_EXTRACT_ALIGNMENT_FACESIZE =
//    "Advanced/FaceExtract/FaceSize";
//static const string ADVANCED_FACE_EXTRACT_PRE_PROCESS =
//    "Advanced/FaceExtract/PreProcess";
static const string ADVANCED_FACE_EXTRACT_METHOD =
    "Advanced/FaceExtract/Method";
static const string ADVANCED_FACE_ALIGN_METHOD =
    "Advanced/FaceAlignment/Method";
static const string ADVANCED_FACE_ALIGN_THRESHOLD =
    "Advanced/FaceAlignment/Threshold";
static const string ADVANCED_FACE_QUALITY_THRESHOLD =
    "Advanced/FaceQuality/BlurThreshold";
static const string ADVANCED_FACE_ENABLE_CONCURRENCY = "Advanced/FaceExtract/EnableConcurrency";
static const string ADVANCED_PLATE_LOCAL_PROVINCE =
    "Advanced/Plate/LocalProvince";
static const string ADVANCED_PLATE_OCR = "Advanced/Plate/OCR";
static const string ADVANCED_PLATE_LOCATE = "Advanced/Plate/Locate";
static const string ADVANCED_PLATE_ENBALE_SHARPEN = "Advanced/Plate/EnableSharp";

static const string DATAPATH = "DataPath";

//static const string FILE_COLOR_MODEL_PATH = "File/Color/ModelPath";
//static const string FILE_COLOR_TRAINED_MODEL = "File/Color/TrainedModel";
//static const string FILE_COLOR_DEPLOY_MODEL = "File/Color/DeployModel";
//
//static const string FILE_STYLE_MODEL_PATH = "File/Style/ModelPath";
//static const string FILE_STYLE_TRAINED_MODEL = "File/Style/TrainedModel";
//static const string FILE_STYLE_DEPLOY_MODEL = "File/Style/DeployModel";
//
//static const string FILE_DETECTION_MODEL_PATH = "File/Detection/ModelPath";
//static const string FILE_DETECTION_TRAINED_MODEL = "File/Detection/TrainedModel";
//static const string FILE_DETECTION_DEPLOY_MODEL = "File/Detection/DeployModel";
//
//static const string FILE_CAR_ONLY_DETECTION_MODEL_PATH = "File/CarOnlyDetection/ModelPath";
//static const string FILE_CAR_ONLY_DETECTION_TRAINED_MODEL = "File/CarOnlyDetection/TrainedModel";
//static const string FILE_CAR_ONLY_DETECTION_DEPLOY_MODEL = "File/CarOnlyDetection/DeployModel";
//
//static const string FILE_CAR_ONLY_CONFIRM_MODEL_PATH = "File/CarOnlyConfirm/ModelPath";
//static const string FILE_CAR_ONLY_CONFIRM_TRAINED_MODEL = "File/CarOnlyConfirm/TrainedModel";
//static const string FILE_CAR_ONLY_CONFIRM_DEPLOY_MODEL = "File/CarOnlyConfirm/DeployModel";
//
//
//static const string FILE_ACCELERATE_MODEL_PATH = "File/Accelerate/ModelPath";
//static const string FILE_ACCELERATE_TRAINED_MODEL = "File/Accelerate/TrainedModel";
//static const string FILE_ACCELERATE_DEPLOY_MODEL = "File/Accelerate/DeployModel";
//
//static const string FILE_MARKER_MODEL_PATH = "File/Marker/ModelPath";
//static const string FILE_MARKER_TRAINED_MODEL = "File/Marker/TrainedModel";
//static const string FILE_MARKER_DEPLOY_MODEL = "File/Marker/DeployModel";
//
//static const string FILE_MARKER_ONLY_MODEL_PATH = "File/MarkerOnly/ModelPath";
//static const string FILE_MARKER_ONLY_TRAINED_MODEL = "File/MarkerOnly/TrainedModel";
//static const string FILE_MARKER_ONLY_DEPLOY_MODEL = "File/MarkerOnly/DeployModel";
//
//static const string FILE_DRIVER_BELT_MODEL_PATH = "File/DriverBelt/ModelPath";
//static const string FILE_DRIVER_BELT_TRAINED_MODEL = "File/DriverBelt/TrainedModel";
//static const string FILE_DRIVER_BELT_DEPLOY_MODEL = "File/DriverBelt/DeployModel";
//
//static const string FILE_CODRIVER_BELT_MODEL_PATH = "File/CoDriverBelt/ModelPath";
//static const string FILE_CODRIVER_BELT_TRAINED_MODEL = "File/CoDriverBelt/TrainedModel";
//static const string FILE_CODRIVER_BELT_DEPLOY_MODEL = "File/CoDriverBelt/DeployModel";
//
//static const string FILE_DRIVER_PHONE_MODEL_PATH = "File/DriverPhone/ModelPath";
//static const string FILE_DRIVER_PHONE_TRAINED_MODEL = "File/DriverPhone/TrainedModel";
//static const string FILE_DRIVER_PHONE_DEPLOY_MODEL = "File/DriverPhone/DeployModel";
//
//
//static const string FILE_PEDESTRIAN_ATTR_MODEL_PATH = "File/PedestrianAttr/ModelPath";
//static const string FILE_PEDESTRIAN_ATTR_TRAINED_MODEL = "File/PedestrianAttr/TrainedModel";
//static const string FILE_PEDESTRIAN_ATTR_DEPLOY_MODEL = "File/PedestrianAttr/DeployModel";
//static const string FILE_PEDESTRIAN_ATTR_TAGNAME_MODEL = "File/PedestrianAttr/TagnameModel";
//static const string FILE_PEDESTRIAN_ATTR_LAYER_NAME = "File/PedestrianAttr/LayerName";
//
//static const string FILE_WINDOW_MODEL_PATH = "File/Window/ModelPath";
//static const string FILE_WINDOW_TRAINED_MODEL = "File/Window/TrainedModel";
//static const string FILE_WINDOW_DEPLOY_MODEL = "File/Window/DeployModel";
//static const string FILE_WINDOW_ONLY_MODEL_PATH = "File/WindowOnly/ModelPath";
//static const string FILE_WINDOW_ONLY_TRAINED_MODEL = "File/WindowOnly/TrainedModel";
//static const string FILE_WINDOW_ONLY_DEPLOY_MODEL = "File/WindowOnly/DeployModel";
//
//static const string FILE_NONMOTORVEHICLE_MODEL_PATH = "File/NonMotorVehicle/ModelPath";
//static const string FILE_NONMOTORVEHICLE_BITRI_TRAINED_MODEL = "File/NonMotorVehicle/BitriTrainedModel";
//static const string FILE_NONMOTORVEHICLE_BITRI_DEPLOY_MODEL = "File/NonMotorVehicle/BitriDeployModel";
//static const string FILE_NONMOTORVEHICLE_UPPER_TRAINED_MODEL = "File/NonMotorVehicle/UpperTrainedModel";
//static const string FILE_NONMOTORVEHICLE_UPPER_DEPLOY_MODEL = "File/NonMotorVehicle/UpperDeployModel";
//static const string FILE_NONMOTORVEHICLE_RPN_TRAINED_MODEL = "File/NonMotorVehicle/RpnTrainedModel";
//static const string FILE_NONMOTORVEHICLE_RPN_DEPLOY_MODEL = "File/NonMotorVehicle/RpnDeployModel";
//static const string FILE_NONMOTORVEHICLE_ATTRIBUTE_FILE = "File/NonMotorVehicle/AttributeFile";

//static const string FILE_FACE_DETECT_MODEL_PATH = "File/FaceDetect/ModelPath";
//static const string FILE_FACE_DETECT_TRAINED_MODEL =
//    "File/FaceDetect/TrainedModel";
//static const string FILE_FACE_DETECT_DEPLOY_MODEL =
//    "File/FaceDetect/DeployModel";
//
//static const string FILE_FACE_EXTRACT_MODEL_PATH = "File/FaceExtract/ModelPath";
//static const string FILE_FACE_EXTRACT_MODEL_DIR = "File/FaceExtract/ModelDir";
//static const string FILE_FACE_EXTRACT_TRAINED_MODEL =
//    "File/FaceExtract/TrainedModel";
//static const string FILE_FACE_EXTRACT_DEPLOY_MODEL =
//    "File/FaceExtract/DeployModel";
//
//static const string FILE_FACE_EXTRACT_MODEL_CONFIG =
//    "File/FaceExtract/ModelConfig";
//
//static const string FILE_FACE_EXTRACT_LAYERNAME = "File/FaceExtract/LayerName";
//static const string FILE_FACE_EXTRACT_MEAN = "File/FaceExtract/Mean";
//static const string FILE_FACE_EXTRACT_PIXEL_SCALE = "File/FaceExtract/PixelScale";
//
//static const string FILE_FACE_EXTRACT_ALIGN_MODEL =
//    "File/FaceExtract/AlignModel";
//static const string FILE_FACE_EXTRACT_ALIGN_DEPLOY = "File/FaceExtract/AlignPic";
//static const string FILE_FACE_EXTRACT_ALIGN_CONFIG =
//    "File/FaceExtract/AlignConfig";
//static const string FILE_FACE_EXTRACT_ALIGN_PATH = "File/FaceExtract/AlignPath";
static const string FILE_PLATE_MODEL_PATH = "File/Plate/ModelPath";
static const string FILE_PLATE_FCN_SYMBOL = "File/Plate/FcnSymbol";
static const string FILE_PLATE_FCN_PARAM = "File/Plate/FcnParam";
static const string FILE_PLATE_RPN_SYMBOL = "File/Plate/RpnSymbol";
static const string FILE_PLATE_RPN_PARAM = "File/Plate/RpnParam";
static const string FILE_PLATE_POLYREG_SYMBOL = "File/Plate/PolyRegSymbol";
static const string FILE_PLATE_POLYREG_PARAM = "File/Plate/PolyRegParam";
static const string FILE_PLATE_ROIP_SYMBOL = "File/Plate/RoipSymbol";
static const string FILE_PLATE_ROIP_PARAM = "File/Plate/RoipParam";
static const string FILE_PLATE_CHRECOG_SYMBOL = "File/Plate/ChrecogSymbol";
static const string FILE_PLATE_CHRECOG_PARAM = "File/Plate/ChrecogParam";
static const string FILE_PLATE_COLOR_SYMBOL = "File/Plate/ColorSymbol";
static const string FILE_PLATE_COLOR_PARAM = "File/Plate/ColorParam";


static const string ADVANCED_PLATE_MXNET_BATCHSIZE = "Advanced/PlateMxnet/BatchSize";
//static const string ADVANCED_PLATE_MXNET_IMGSW = "Advanced/PlateMxnet/ImgStandardWidth";
//static const string ADVANCED_PLATE_MXNET_IMGSH = "Advanced/PlateMxnet/ImgStandardHeight";
//static const string ADVANCED_PLATE_MXNET_PLATESW = "Advanced/PlateMxnet/PlateStandardWidth";
//static const string ADVANCED_PLATE_MXNET_PLATESH = "Advanced/PlateMxnet/PlateStandardHeight";
//static const string ADVANCED_PLATE_MXNET_PLATENUMS = "Advanced/PlateMxnet/PlateNums";
//static const string ADVANCED_PLATE_MXNET_NUMSPROPOSAL = "Advanced/PlateMxnet/NumsProposal";
static const string ADVANCED_PLATE_MXNET_ENABLE_LOCALPROVINCE = "Advanced/PlateMxnet/EnableLocalProvince";
static const string ADVANCED_PLATE_MXNET_LOCALPROVINCE_TEXT = "Advanced/PlateMxnet/LocalProvinceText";
static const string ADVANCED_PLATE_MXNET_LOCALPROVINCE_CONFIDENCE = "Advanced/PlateMxnet/LocalProvinceConfidence";

static const string ADVANCED_RANKER_REPO_PATH = "Advanced/Ranker/RepoPath";
static const string ADVANCED_RANKER_IMAGE_ROOT_PATH = "Advanced/Ranker/ImageRootPath";
static const string ADVANCED_RANKER_FEATURE_LENGTH = "Advanced/Ranker/FeatureLen";
static const string ADVANCED_RANKER_MAXIMUM = "Advanced/Ranker/Maximum";
static const string ADVANCED_RANKER_NORMALIZE_ALPHA = "Advanced/Ranker/NormalizeAlpha";
static const string ADVANCED_RANKER_NORMALIZE_BETA = "Advanced/Ranker/NormalizeBeta";
static const string ADVANCED_RANKER_NEED_SAVE_TO_FILE = "Advanced/Ranker/SaveToFile";
static const string ADVANCED_RANKER_SAVE_TO_FILE_ITERVAL = "Advanced/Ranker/SaveToFileIterval";


static const string DEBUG_VISUALIZATION = "Debug/Visualization";
}

#endif /* ENGINE_CONFIG_VALUE_H_ */
