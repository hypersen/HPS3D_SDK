************************************************** *****************************
Readme HPS_3DTOF HPS3D_SDK

Hypersen Technologies Copyright © 2019 Version 20.3.19
************************************************** *****************************
The HPS3D_SDK update is as follows:

V1.7.7:
1. The obstacle extraction algorithm is integrated: support for extracting obstacle feature information values ​​(including three-dimensional coordinate values ​​of obstacle left end, right end point, upper end point, lower end point, closest point, and average distance of obstacles, pixel points) Number, etc.)
Instructions for use:
a, enable point cloud conversion - get point cloud data - HPS3D_SetPointCloudEn (true);
b, configuration obstacle extraction related parameters - HPS3D_ObstacleConfigInit (...);
c. The obstacle extraction result is saved in Obstacle_data in the MeasureDataTypeDef structure.
Note: To modify the obstacle extraction default configuration parameters (pixel count threshold and threshold offset), the following interfaces are required:
Set the threshold number of obstacle pixels --- HPS3D_SetObstaclePixelNumberThreshold(...);
Get the threshold number of obstacle pixels---HPS3D_GetObstaclePixelNumberThreshold(...);
Set obstacle extraction threshold offset ---- HPS3D_SetThresholdOffset(...);
   Get obstacle extraction threshold offset ----- HPS3D_GetThresholdOffset(...);
2, the new access to the SDK version information interface function --- Version_t HPS3D_GetSDKVersion (...);
Note: If the firmware version does not match the SDK version, please upgrade the firmware before using the SDK.
3. Added special configuration values ​​for measurement results (65300, 65400, 65500, 65530, etc.) configuration interface:
   Convert special measurement output values ​​to specified special value parameter configuration-----HPS3D_ConfigSpecialMeasurementValue(...);
Description: This interface function converts the special value returned by the sensor measurement to the specified invalid measurement value;

4, the new edge noise filtering algorithm has been added, just call the set edge noise filtering enable interface function --- HPS3D_SetEdgeDetectionEnable(...);
Related parameters configuration interface function (default, generally do not need to set the following parameters):
Get edge noise filtering enable ---extern bool HPS3D_GetEdgeDetectionEnable(void);
Set the edge noise threshold ---extern RET_StatusTypeDef HPS3D_SetEdgeDetectionValue(int32_t threshold_value);
Get the edge noise threshold ---extern int32_t HPS3D_GetEdgeDetectionValue(void);

V1.7.8
1. Optimize the bending phenomenon of point cloud data
     ●Note: If the point cloud conversion is enabled, the bending phenomenon still occurs. Please check whether the optical compensation parameter is enabled.
     HPS3D_GetOpticalParamConf(...)----Get optical compensation parameters
     HPS3D_SetOpticalEnable(...)----Optical compensation enable setting
     ● Point cloud data conversion only needs to enable point cloud conversion. After enabling, the data is saved in point_cloud_data in MeasureData.
HPS3D_SetPointCloudEn(...) ----Point cloud conversion enable setting
2. Add point cloud data to save as ply format file (displayed by Meshlab software), which is convenient for analyzing point cloud data.
    HPS3D_SavePlyFile(...) ---- Save as point file data in ply file format

V1.7.9
1. Modify the installation angle to set the interface function:
Cancel the setting installation angle enable interface function: HPS3D_SetMountingAngleEnable();
The installation angle transformation parameter setting has been added: installation height parameter setting HPS3D_SetMountingAngleParamConf();
The purpose of modifying the above interface is to rotate and translate the point cloud coordinates measured by the camera with the mounting angle, which is convenient for analyzing the point cloud coordinates.

V1.7.10
1, join the Ethernet version to set the server IP and server IP reset interface
     HPS3D_SetEthernetServerInfo(...) This function needs to be called to match the server IP before connecting. The default server IP is 192.168.0.10.
     HPS3D_ConfigEthernet (.....) resets the server IP. If you need to modify the sensor default IP, you can call this function to set it. After the setting is completed, you need to save the communication configuration (HPS3D_SaveTransportConf(.....)) to make it permanent. Otherwise, power off. Restore the factory default IP

V1.7.11
1. Join the automatic connection device and initialize the configuration interface.
HPS3D_AutoConnectAndInitConfigDevice(); This interface supports simultaneous connection of multiple devices;
   This interface replaces the original three combinations of HPS3D_GetDeviceList() + HPS3D_Connect() + HPS3D_ConfigInit(), and the original interface remains unchanged.
2, join the point cloud data mirroring function
HPS3D_SetPointCloudMirrorType(); The purpose of this interface is to mirror the point cloud data. Currently, horizontal mirroring and vertical mirroring are supported.

V1.7.12
1, join the RS232 version to set the baud rate and other parameter configuration interface
HPS3D_SetUartConfig(); This interface needs to be configured before the connection;
2, join the multi-machine code setting
Multi-machine cooperative coding is to solve the phenomenon that optical signals interfere with each other when working in multiple devices. By setting each device to a different multi-machine number, the interference can be eliminated.
HPS3D_SetMultiCameraCode(); Note: The bending of the point cloud conversion is still enabled. Please check if the optical compensation parameter is enabled.
3, repair multi-device connection often communication failure and ROI packet return exception, etc.

V1.7.13
1, repair FULL_ROI_DATA packet exception phenomenon