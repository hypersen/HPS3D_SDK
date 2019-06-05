*******************************************************************************
Readme HPS_3DTOF HPS3D_SDK 

Hypersen Technologies Copyright ©  2019                  Version 20.3.19
*******************************************************************************
HPS3D_SDK 更新内容如下:

V1.7.7：
1、融合了障碍物提取算法：支持提取障碍物特征信息值(包含障碍物左端点、右端点、上端点、下端点、最近点的三维空间坐标值,以及障碍物的平均距离、像素点个数等)
使用说明：
	a、使能点云转换--得到点云数据--HPS3D_SetPointCloudEn(true);
	b、配置障碍物提取相关从参数--HPS3D_ObstacleConfigInit(...);
	c、障碍物提取结果保存在MeasureDataTypeDef结构体中的Obstacle_data中
注：如需修改障碍物提取默认配置参数(像素点个数阈值以及阈值偏置)则需使用以下接口：
	设置障碍物像素点个数阈值---HPS3D_SetObstaclePixelNumberThreshold(...);
	获取障碍物像素点个数阈值---HPS3D_GetObstaclePixelNumberThreshold(...);
	设置障碍物提取阈值偏置-----HPS3D_SetThresholdOffset(...);
   	获取障碍物提取阈值偏置-----HPS3D_GetThresholdOffset(...);	
2、新增了获取SDK版本信息接口函数---Version_t HPS3D_GetSDKVersion(...);
注：若固件版本与SDK版本不匹配,请先升级固件后再使用该SDK
3、新增了测量结果特殊值(65300,65400,65500,65530等)配置接口：
   将特殊测量输出值转换为指定特殊值参数配置-----HPS3D_ConfigSpecialMeasurementValue(...);
说明：该接口功能将传感器测量返回的特殊值转换为指定无效测量值;

4、新增了边缘噪声滤除算法,仅需调用设置边缘噪声滤除使能接口函数---HPS3D_SetEdgeDetectionEnable(...);
相关参数配置接口函数(默认即可，一般情况下不需设置以下参数)：
	获取边缘噪声滤除使能 ---extern bool HPS3D_GetEdgeDetectionEnable(void);
	设置边缘噪声阈值 ---extern RET_StatusTypeDef HPS3D_SetEdgeDetectionValue(int32_t threshold_value);
	获取边缘噪声阈值 ---extern int32_t HPS3D_GetEdgeDetectionValue(void);

V1.7.8
1、对点云数据弯曲现象进行优化处理
     ●注：使能点云转换仍出现弯曲现象，请检查光学补偿参数是否使能
     	HPS3D_GetOpticalParamConf(...)----获取光学补偿参数
     	HPS3D_SetOpticalEnable(...)----光学补偿使能设置
     ●点云数据转换仅需使能点云转换即可，使能后数据保存在MeasureData中的point_cloud_data中
		HPS3D_SetPointCloudEn(...) ----点云转换使能设置
2、加入点云数据保存为ply格式文件(可用Meshlab软件进行显示)，便于对点云数据进行分析
    	HPS3D_SavePlyFile(...)  ----保存为ply文件格式点云数据

V1.7.9
1、修改安装角度设定接口函数：
取消了设定安装角度使能接口函数：HPS3D_SetMountingAngleEnable()；
安装角度变换参数设定中加入了:安装高度参数设定HPS3D_SetMountingAngleParamConf();
修改以上接口目的是将带有安装角度的相机测量得到的点云坐标进行旋转及平移处理，便于对点云坐标进行分析

V1.7.10
1、加入以太网版本设置服务器IP以及服务器IP重置等接口
     HPS3D_SetEthernetServerInfo(......) 连接前需要调用此函数进行服务器IP匹配，默认服务器IP为192.168.0.10
     HPS3D_ConfigEthernet（.....）重置服务器IP，如需修改传感器默认IP可以调用此函数进行设置，设置完成后需要保存通信配置(HPS3D_SaveTransportConf(.....))使得永久生效，否则断电即恢复出厂默认IP

V1.7.11
1、加入自动连接设备并进行初始化配置接口
	HPS3D_AutoConnectAndInitConfigDevice();此接口可支持同时连接多台设备；
   该接口替换了原有的 HPS3D_GetDeviceList() + HPS3D_Connect() + HPS3D_ConfigInit()等三个接口组合，原有接口仍保持不变
2、加入点云数据镜像功能
	HPS3D_SetPointCloudMirrorType();此接口目的是将点云数据进行镜像处理，目前支持水平镜像与垂直镜像处理
	
V1.7.12
1、加入RS232版本设置波特率等参数配置接口
	HPS3D_SetUartConfig();此接口需要在连接前进行配置;
2、加入多机编码设定
	多机协作编码是为了解决多设备同是工作时相互之间光信号干扰等现象，将各设备设置为不同的多机编号后便可消除此干扰
	HPS3D_SetMultiCameraCode(); 注：使能点云转换仍出现弯曲现象，请检查光学补偿参数是否使能
3、修复多设备连接经常通信失败及ROI数据包返回异常等问题

V1.7.13
1、修复FULL_ROI_DATA数据包异常现象

V1.7.14
1、为更好的跨平台使用，修改了api.h文件，其中
	FullRoiDataTypeDef中的distance[MAX_PIXEL_NUM]===> *distance;
	DepthDataTypeDef中的distance[MAX_PIXEL_NUM]===> *distance;
	ObstacleDataTypedef中的PixelBuffer[MAX_PIXEL_NUM]===> *PixelBuffer;
	PointCloudDataTypeDef中的point_data[MAX_PIXEL_NUM]===> *point_data;
	
V1.7.15
1、加入心跳检测机制，判断通信是否异常断开连接
HPS3D_SetKeepAliveConfig(...) :设置心跳检测时间，在设定完成后必须定时发送心跳包给传感器，否则设备在超时后将自动停止工作；调用此接口配置完成后，需在连续测量前发送一次心跳包给传感器使用以下接口
HPS3D_SendKeepAlive(...) :设置保活，需在设定检测时间内发送保活指令，确保传感器持续工作；发送此命令后回调函数中会产生相应的返回包KEEP_ALIVE_PACKET，可通过计算两次返回包的时间差来检测心跳是否存在
