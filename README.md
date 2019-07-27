# HPS3D_SDK
The current project includes Demo programs under Linux, ros, windows and other platforms. For details, please refer to HPS-3D160 Solid-state Depth camera SDK manual.

V1.7.18
1. Fix point cloud data mirroring function HPS3D_SetPointCloudMirrorType(...);
2. Add the device serial number interface HPS3D_GetSerialNumber();

V1.7.17
1. Add settings / get the maximum integration time, set / get the minimum signal amplitude interface
HPS3D_SetMaxIntegTime(...)/ HPS3D_GetMaxIntegTime(...)
HPS3D_SetMinAmpliude(...)/HPS3D_GetMinAmplitude(...)

V1.7.16
1. Add multiple devices to splicing and use related interfaces
2, repair the HPS3D_RemoveDevice () interface

V1.7.15
1. Add a heartbeat detection mechanism to determine whether the communication is abnormally disconnected.

V1.7.14
1. For better cross-platform use, modify the api.h file, where
FullRoiDataTypeDef:   Distance[MAX_PIXEL_NUM]===> *distance;
DepthDataTypeDef:     Distance[MAX_PIXEL_NUM] ===> *distance;
ObstacleDataTypedef:  PixelBuffer[MAX_PIXEL_NUM]===> *PixelBuffer
PointCloudDataTypeDef:Point_data[MAX_PIXEL_NUM]===> *point_data;

