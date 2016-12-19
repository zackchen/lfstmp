{
    "Version": {
        "Code": "1.0.0", 
        "Model": "1.9"
    },
    "ProtocolType": "restful",
   //   "ProtocolType": "rpc|restful",
    "InstanceType": "witness",
   // "InstanceType" : "ranker",
    "System": {
        "Ip": "0.0.0.0",
        "Port": 6500,
        "Threads": [1]
    },
    "RankerType": "car|face",
    "Pack":{
        "Enable":false,
        "BatchSize":1,
        "TimeOut":100
    },
    "ModelPath": {
        "dgvehicle":"data/dgvehicle"
    },
    "Feature": {
        "Vehicle": {
            "Enable": true,
            "EnableDetection": true,
            "EnableType": true,
            "EnableColor": true,
            "EnablePlate": false,
            "EnableGpuPlate": true,
            "EnablePlateEnhanced": false,
            "EnableMarker": true,
            "EnableDriverBelt": false,
            "EnableCoDriverBelt": true,
            "EnablePhone": true,
            "EnableFeatureVector": true,
            "EnableNonMotorVehicle": true,
            "EnablePedestrianAttr": true
        },
        "Face": {
            "Enable": false,
            "EnableDetection": false,
            "EnableFeatureVector": false
        }
    },
    "Advanced": {
        "Detection": {
            "Rescale": 400,
            "TargetMinSize": 400.0,
            "TargetMaxSize": 600.0,
            "CarOnly": false,
            "BatchSize": 1
        },
        "Color": {
            "BatchSize": 1,
            "ModelNum": 1
        },
        "Style": {
            "BatchSize": 1,
            "ModelNum": 1
        },
        "Plate": {
            "LocalProvince": "",
            "OCR": 1,
            "Locate": 5,
            "EnableSharp": false
        },
        "PlateMxnet": {
            "BatchSize": 1, 
            "EnableLocalProvince": false, 
            "ImgStandardHeight": 600, 
            "ImgStandardWidth": 400, 
            "LocalProvinceConfidence": 0.6, 
            "LocalProvinceText": "\u4eac", 
            "NumsProposal": 20, 
            "PlateNums": 4, 
            "PlateStandardHeight": 150, 
            "PlateStandardWidth": 250
        }, 
        "Marker": {
            "MOTConfidence": 0.6,
            "BeltConfidence": 0.8,
            "GlobalConfidence": 0.8,
            "AccessoriesConfidence": 0.8,
            "OthersConfidence": 0.8,
            "TissueBoxConfidence": 0.8,
            "SunVisorConfidence": 0.8,
            "BatchSize": 2
        },
        "DriverBelt": {
            "BatchSize": 2
        },
        "CoDriverBelt": {
            "BatchSize": 2
        },
        "DriverPhone": {
            "BatchSize": 2
        },
        "Window": {
            "BatchSize": 1
        },
        "FaceDetect": {
            "BatchSize": 1,
            "Confidence": 0.7,
            "BodyRelativeFaceLeft": 0.2,
            "BodyRelativeFaceRight": 0.2,
            "BodyRelativeFaceTop": 0.2,
            "BodyRelativeFaceBottom": 6.0,
            "Scale": 640
        },
        "FaceExtract": {
            "BatchSize": 1
        },
        "Ranker": {
            "Maximum": 100000
        },
        "PersonReid": {
            "BatchSize": 1,
            "InputWidth":20,
            "InputHeight":20,
            "CropWidth":20,
            "CropHeight":10
        },
        "CarReid": {
            "BatchSize": 1,
            "InputWidth":20,
            "InputHeight":20,
            "CropWidth":20,
            "CropHeight":10
        },
        "ParseImageTimeout": 60
    },
    "Log": {
        "Dir": "",
        "Level": ""
    },
    "Render": {
        "NonMotorVehicle": {
            "NonMotorAttr": "data/mapping/bitri_attr_type.txt", 
            "NonMotorCategory": "data/mapping/bitri_attr_category.txt"
        }, 
        "Pedestrian": {
            "PedestrianAttr": "data/mapping/pedestrian_attr_type.txt", 
            "PedestrianCategory": "data/mapping/pedestrian_attr_category.txt"
        }, 
        "Vehicle": {
            "Color": "data/mapping/vehicle_color.txt", 
            "Model": "data/mapping/vehicle_style_v1.12_4063.txt", 
            "Plate": {
                "Color": "data/mapping/plate_color.txt", 
                "ColorGpu": "data/mapping/plate_gpu_color.txt", 
                "Type": "data/mapping/plate_type.txt"
            }, 
            "Symbol": "data/mapping/vehicle_symbol.txt", 
            "Type": "data/mapping/vehicle_type.txt"
        }
    },
    "Debug": {
        "Enable": true,
        "EnableCutboard": true,
        "Encrypt": false,
        "Visualization": false
    },
    "Storage": {
        "Address": [
            "192.168.2.119:9004", 
            "192.168.2.132:9877", 
            "./"
        ], 
        "DBType": [
            0, 
            1, 
            2
        ], 
        "Enabled": false
    },

    //"DataPath": "data/data_tollgate.dat"
    "DataPath": "data/data.dat"
}