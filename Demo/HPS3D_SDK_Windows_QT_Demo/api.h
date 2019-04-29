/**********************************************************************
* COPYRIGHT NOTICE - HYPERSEN TECHNOLOGY
*
* Copyright (c) 2018, Hypersen Technology, Inc.
*
* All rights reserved.
*
*======================================================================
* \file api.h
* \brief TODO
* \author Kevin
* \email Kevin_Wang@hypersen.com
* \version 1.0.0
* \date 2018年11月13日 上午11:43:31
* \license private & classified
*---------------------------------------------------------------------
* Remark: This project is still under construction.
*======================================================================
* Change History:
*---------------------------------------------------------------------
* <Date>			| <Version>	| <Author>			| <Description>
*---------------------------------------------------------------------
* 2018年11月13日			| V1.0.0	| Kevin				| Create file
*======================================================================
* Detailed Notes:
*---------------------------------------------------------------------
* <Version>		| <Description>
*---------------------------------------------------------------------
* V1.0.0		| TODO
*---------------------------------------------------------------------

**********************************************************************/

#ifndef HPS3D_API_H_
#define HPS3D_API_H_

#ifdef __cplusplus
extern "C"  /*C++*/
{
#endif

#include <stdbool.h>
#include <string.h>


#ifdef _WIN32 /*windows平台*/
	#include <windows.h>
	#include <winsock2.h>
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
#endif

#define DLL_API _declspec(dllexport)

/*类型的宏*/
typedef signed char 	int8_t;
typedef unsigned char 	uint8_t;
typedef unsigned short 	uint16_t;
typedef short 			int16_t;
typedef unsigned int 	uint32_t;
typedef int 			int32_t;
typedef float 			float32_t;
typedef double 			float64_t;


#define 	DEV_NUM 			 (10)							/*设备数量*/
#define     DEV_NAME_SIZE		 (20)							/*设备名长度*/
#define 	ROI_NUM 			 (8)							/*ROI的数量*/
#define 	OBSTACLE_NUM 		 (20)							/*支持障碍物数量*/
#define 	OBSERVER_NUM  		 (10)							/*观察者数量*/

/*	分辨率	*/
#define		RES_WIDTH			 (160)							/*深度图的长度*/
#define		RES_HEIGHT			 (60)							/*深度图的宽度*/
#define		MAX_PIX_NUM 		 (RES_WIDTH * RES_HEIGHT)		/*最大的深度图像素*/

/*特殊测量数据值*/
#define	 	LOW_AMPLITUDE   	(65300) 						/*信号幅值低*/
#define	  	SATURATION 			(65400)     					/*饱和位饱和*/
#define	 	ADC_OVERFLOW  		(65500)   						/*ADC溢出*/
#define	 	INVALID_DATA 		(65530)    						/*无效数据*/

/*函数返回的结果*/
typedef enum
{
	RET_OK 		= 0x01,		/*返回成功*/
	RET_ERROR 	= 0x02,		/*返回错误*/
	RET_BUSY 	= 0x03,		/*返回忙*/
	RET_CONNECT_FAILED,     /*连接失败*/
	RET_CREAT_PTHREAD_ERR,  /*线程创建失败*/
	RET_WRITE_ERR,          /*写失败*/
	RET_READ_ERR,           /*读失败*/
	RET_PACKET_HEAD_ERR,    /*报头错误*/
	RET_PACKET_ERR,    		/*报文错误*/
	RET_BUFF_EMPTY,			/*缓冲区为空*/
	RET_VER_MISMATCH,  		/*版本不匹配*/
}RET_StatusTypeDef;

/*设备版本*/
typedef struct
{
	uint8_t year;			/*年*/
	uint8_t month;			/*月*/
	uint8_t day;			/*日*/
	uint8_t major;			/*主板本*/
	uint8_t minor;			/*次版本*/
	uint8_t rev;			/*修订次数*/
}Version_t;

/*运行模式选择*/
typedef enum
{
	MinOfRunModeType = 0,
	RUN_IDLE = 0,			/*运行停止*/
	RUN_SINGLE_SHOT,		/*单次测量*/
	RUN_CONTINUOUS,			/*多次测量*/
	NumberOfRunModeType
}RunModeTypeDef;

/*设置测量数据包类型*/
typedef enum
{
	DEPTH_DATA_PACKET = 0x0,  /*深度数据包*/
	ROI_DATA_PACKET,		  /*ROI数据包*/
	OBSTACLE_PACKE			  /*障碍物数据包*/
}MeasurePacketTypeDef;


/*设置输出数据包的类型*/
typedef enum
{
	PACKET_FULL = 0,		/*完整数据包（包含深度数据）*/
	PACKET_SIMPLE			/*简单数据包（不包含深度数据）*/
}OutPacketTypeDef;


/*ROI的阈值警报类型*/
typedef enum
{
	ROI_ALARM_DISABLE = 0,  /*关闭ROI区域警报，仅输出ROI区域的信息和数据*/
	ROI_ALARM_GPIO       	/*ROI区域警报类型为GPIO OUT电平输出*/
}ROIAlarmTypeDef;

/*单点的迟滞配置*/
typedef struct
{
	uint8_t threshold_id;  		    /*敏感区域阈值id*/
	uint32_t threshold_value; 		/*敏感区域阈值*/
	uint32_t hysteresis; 			/*迟滞大小*/
	bool enable;					/*迟滞使能*/
	bool positive;					/*true:正向比较，如果输入值大于阈值则返回True
									false:反向比较，如果输入值小于阈值则返回False*/
}HysteresisSingleConfTypeDef;

/*ROI的参考值类型*/
typedef enum
{
	ROI_REF_DIST_AVR = 1,			/*ROI区域的距离平均值作为参考值*/
	ROI_REF_DIST_MIN,				/*ROI区域的距离最小值作为参考值*/
	ROI_REF_DIST_MAX,				/*ROI区域的距离最大值作为参考值*/
	ROI_REF_SAT_COUNT,				/*ROI区域的饱和像素点数量作为参考值*/
	ROI_REF_AMPLITUDE,				/*ROI区域的幅值平均值作为参考值*/
	ROI_REF_VAILD_AMPLITUDE,		/*ROI区域的有效幅值平均值作为参考值*/
	ROI_REF_THRESHOLD_PIX_NUM		/*超过设定阈值的像素点数，相比最大值比较和最小值比较具有更高的可靠性*/
}ROIReferenceTypeDef;

/*ROI配置的结构体*/
 typedef struct
{
	bool enable;										/*使能标识*/
	uint8_t roi_id;										/*ROI的ID*/
	uint16_t left_top_x;								/*左上角x坐标*/
	uint16_t left_top_y;								/*左上角y坐标*/
	uint16_t right_bottom_x;							/*右下角x坐标*/
	uint16_t right_bottom_y;							/*右下角y坐标*/
	HysteresisSingleConfTypeDef hysteresis_conf[3];		/*单点的迟滞配置*/
	ROIReferenceTypeDef ref_type[3];					/*ROI的参考值类型,与hysteresis_conf一一对应*/
	ROIAlarmTypeDef alarm_type[3];						/*ROI的阈值警报类型,与hysteresis_conf一一对应*/
	uint16_t pixel_number_threshold[3];					/*超过阈值的像素点数阈值,与hysteresis_conf一一对应*/
}ROIConfTypeDef;

/*Auto HDR调节模式*/
typedef enum
{
	HDR_DISABLE = 0,				/*HDR不使能，手动设置/获取 积分时间*/
	AUTO_HDR,						/*自动HDR，设置/获取 曝光幅值/过度曝光幅值/信号弱幅值/信号极弱幅值*/
	SUPER_HDR,						/*超级HDR，设置/获取 合成帧数/最大积分时间*/
	SIMPLE_HDR						/*简单HDR，设置/获取 最大/最小积分时间*/
}HDRModeTypeDef;

/*HDR配置*/
typedef struct
{
	HDRModeTypeDef hdr_mode;					/*HDR模式选择*/
	float32_t qualtity_overexposed;				/*AUTO_HDR 曝光幅值*/
	float32_t qualtity_overexposed_serious;		/*AUTO_HDR 过度曝光赋值*/
	float32_t qualtity_weak;					/*AUTO_HDR 信号弱幅值*/
	float32_t qualtity_weak_serious;			/*AUTO_HDR 信号极弱幅值*/
	uint32_t simple_hdr_max_integration;		/*SIMPLE_HDR 最大积分时间 us*/
	uint32_t simple_hdr_min_integration;		/*SIMPLE_HDR 最小积分时间 us*/
	uint8_t super_hdr_frame_number;				/*SUPER_HDR 合成帧数*/
	uint32_t super_hdr_max_integration;			/*SUPER_HDR 最大积分时间 us*/
	uint32_t hdr_disable_integration_time;		/*HDR_DISABLE 手动积分时间 us*/
}HDRConf;

/*平滑滤波器的类型*/
typedef enum
{
	SMOOTH_FILTER_DISABLE = 0,		/*平滑滤波器关闭*/
	SMOOTH_FILTER_AVERAGE = 1,		/*均值滤波器*/
	SMOOTH_FILTER_GAUSS				/*高斯滤波器*/
}SmoothFilterTypeDef;

/*平滑滤波器的配置结构体*/
typedef struct
{
	SmoothFilterTypeDef type;		/*设置平滑滤波器模式*/
	uint32_t arg1;					/*滤波参数*/
}SmoothFilterConfTypeDef;

/*GPIO配置的相关定义*/
/*GPIO_OUT功能*/
typedef enum
{
	GPOUT_FUNC_DISABLE = 0,				/*GPIO报警关闭*/
	GPOUT_FUNC_ROI_THRESHOLD0_ALARM,	/*GPIO输出阈值0警报*/
	GPOUT_FUNC_ROI_THRESHOLD1_ALARM,	/*GPIO输出阈值1警报*/
	GPOUT_FUNC_ROI_THRESHOLD2_ALARM		/*GPIO输出阈值2警报*/
}GPOutFunctionTypeDef;

/*GPIO_IN功能*/
typedef enum
{
	GPIN_FUNC_DISABLE = 0,			/*GPIO功能关闭*/
	GPIN_FUNC_CAPTURE   			/*开启测量  注：开启测量后，则不受命令控制，只受IO输入控制*/
}GPInFunctionTypeDef;

/*GPIO极性*/
typedef enum
{
	GPIO_POLARITY_LOW = 0,			/*GPIO极性为低*/
	GPIO_POLARITY_HIGH				/*GPIO极性为高*/
}GPIOPolarityTypeDef;

/*GPIO引脚*/
typedef enum
{
    GPIN_1 = 1,         /*输入*/
    GPIN_2 = 2,
    GPIN_3 = 3,
    GPOUT_1 = 10,		/*输出*/
    GPOUT_2 = 11,
    GPOUT_3 = 12,
}GPIOTypeDef;

/*GPIO输出配置*/
typedef struct
{
	GPIOTypeDef gpio;				/*GPIO引脚*/
	GPIOPolarityTypeDef polarity;	/*GPIO极性*/
	GPOutFunctionTypeDef function;	/*GPIO功能*/
}GPIOOutConfTypeDef;

/*GPIO输入配置*/
typedef struct
{
	GPIOTypeDef gpio;				/*GPIO引脚*/
	GPIOPolarityTypeDef polarity;	/*GPIO极性*/
	GPInFunctionTypeDef function;	/*GPIO功能*/
}GPIOInConfTypeDef;


/*距离滤波器类型*/
typedef enum
{
	DISTANCE_FILTER_DISABLE = 0,	/*距离滤波器关闭*/
	DISTANCE_FILTER_SIMPLE_KALMAN	/*简单卡尔曼滤波器*/
}DistanceFilterTypeDef;

typedef struct
{
	DistanceFilterTypeDef filter_type;		/*距离滤波器类型*/
	float32_t kalman_K; 					/*简单卡尔曼滤波器比例系数*/
	uint32_t kalman_threshold;				/*噪声阈值*/
	uint32_t num_check;						/*阈值检查帧数*/
}DistanceFilterConfTypeDef;

/*安装角度变换参数,旋转坐标系使用*/
typedef struct
{
	bool enable;					/*安装角度使能*/
	uint8_t angle_vertical;     	/*垂直方向安装角度（°）:主光轴与地垂线间的夹角*/
	uint16_t height;				/*相对于地面的安装高度(mm)*/
}MountingAngleParamTypeDef;

/*解析数据包的类型*/
typedef enum
{
	NULL_PACKET = 0x00,				/*数据返回为空*/
	SIMPLE_ROI_PACKET = 0x01,		/*简单ROI数据包（不含深度图数据）*/
	FULL_ROI_PACKET,				/*完整ROI数据包（含深度图数据）*/
	FULL_DEPTH_PACKET,				/*完整深度数据包（含深度图数据）*/
	SIMPLE_DEPTH_PACKET,			/*简单深度数据包（不含深度图数据）*/
	OBSTACLE_PACKET,				/*障碍物数据包 */
    SYSTEM_ERROR					/*系统错误*/
}RetPacketTypedef;

/*简单数据包的ROI数据*/
typedef struct
{
	uint8_t group_id;						/*组ID*/
	uint8_t id;								/*ROI ID*/
	uint16_t amplitude;						/*平均幅值*/
	uint16_t valid_amplitude;				/*平均有效幅值*/
	uint16_t distance_average;				/*平均距离值*/
	uint16_t distance_max;					/*最大距离值*/
	uint16_t distance_min;					/*最小距离值*/
	uint16_t dist_max_x;					/*最大距离的x坐标*/
	uint16_t dist_max_y;					/*最大距离的y坐标*/
	uint16_t dist_min_x;					/*最小距离的x坐标*/
	uint16_t dist_min_y;					/*最小距离的y坐标*/
	uint16_t saturation_count;				/*饱和像素点数*/
	uint8_t threshold_state;				/*当前测量值是否超出阈值:bit0:zone0, bit1:zone1, bit2:zone2*/
	uint16_t out_of_threshold_pix_num[3];	/*[0]:超过thresold0的像素点数,[1]:...,[2]:...*/
	uint16_t frame_cnt;						/*帧计数器*/
}SimpleRoiDataTypeDef;

/*全部数据包的ROI深度图数据*/
typedef struct
{
	uint8_t roi_num;						/*ROI总数量*/
	uint8_t group_id;						/*组ID*/
	uint8_t id;								/*ROI ID*/
	uint16_t left_top_x;					/*左上角x坐标*/
	uint16_t left_top_y;					/*左上角y坐标*/
	uint16_t right_bottom_x;				/*右下角x坐标*/
	uint16_t right_bottom_y;				/*右下角y坐标*/
	uint32_t pixel_number;					/*ROI像素点*/
	uint16_t amplitude;						/*平均幅值*/
	uint16_t valid_amplitude;				/*平均有效幅值*/
	uint16_t distance_average;				/*平均距离值*/
	uint16_t distance_max;					/*最大距离值*/
	uint16_t distance_min;					/*最小距离值*/
	uint16_t saturation_count;				/*饱和像素点数*/
	uint16_t threshold_state;				/*当前测量值是否超出阈值:bit0:zone0, bit1:zone1, bit2:zone2*/
	uint16_t dist_max_x;					/*最大距离的x坐标*/
	uint16_t dist_max_y;					/*最大距离的y坐标*/
	uint16_t dist_min_x;					/*最小距离的x坐标*/
	uint16_t dist_min_y;					/*最小距离的y坐标*/
	uint32_t frame_cnt;						/*帧计数器*/
	uint16_t distance[MAX_PIX_NUM];			/*深度数据，按顺序储存*/
}FullRoiDataTypeDef;

/*深度图数据*/
typedef struct
{
	uint16_t distance_average;				/*平均距离值*/
	uint16_t amplitude_average;				/*平均有效幅值*/
	uint16_t amplitude_average_whole;		/*平均所有幅值*/
	uint16_t amplitude_low_count;			/*低信号像素的数量*/
	uint16_t saturation_count;				/*饱和像素点数*/
	uint16_t distance_max;					/*最大距离值*/
	uint16_t distance_min;					/*最小距离值*/
	int16_t temperature;					/*温度值*/
	uint16_t frame_cnt;						/*帧计数器*/
	uint16_t interference_num;				/*受干扰的像素点*/
	uint16_t distance[MAX_PIX_NUM];			/*深度数据，按顺序储存*/
}DepthDataTypeDef;


/*每点的点云数据*/
typedef struct
{
	float32_t x;					/*x,y,z空间坐标*/
	float32_t y;
	float32_t z;
}PerPointCloudDataTypeDef;

/*有序点云数据*/
typedef struct
{
	PerPointCloudDataTypeDef point_data[MAX_PIX_NUM];	/*点云坐标，数组是为了存储多个ROI*/
	uint16_t width;										/*宽度：一行，点的数目*/
	uint16_t height;									/*高度：行的总数*/
	uint32_t points;									/*点云图，点的总数*/
}PointCloudDataTypeDef;

/*障碍物配置相关参数*/
typedef struct
{
	bool enable;       				/*使能标志位*/
	uint16_t frame_head; 			/*数据帧，帧头特征字节，例如0XEB81*/
	uint8_t number;  				/*需要提取的障碍物数量 例如3*/
	uint16_t vaild_min_dist; 		/*有效范围的最小距离值mm 例如 600*/
	uint16_t vaild_max_dist; 		/*有效范围的最大距离值mm 例如 3500*/
	uint16_t invaild_value;  		/*无效区域的固定参数值mm 例如 5000*/
	uint16_t frame_size;			/*保存当前缓冲区有效字节数*/
}ObstacleConfigTypedef;

/*障碍物数据*/
typedef struct
{
	uint8_t ObstacleNumber;								/*所提取到障碍物的总数*/
	uint8_t Id;   										/*障碍物区域ID*/
	uint32_t FrameCount;  								/*帧计数值*/
	uint16_t PixelNumber;			 					/*障碍物区域内像素点总数*/
	uint16_t DistanceAverage; 							/*障碍物区域内平均距离值*/
	PerPointCloudDataTypeDef LeftPoint; 				/*障碍物区域左端点坐标值*/
	PerPointCloudDataTypeDef RightPoint; 				/*障碍物区域右端点坐标值*/
	PerPointCloudDataTypeDef UpperPoint; 				/*障碍物区域上端点坐标值*/
	PerPointCloudDataTypeDef UnderPoint; 				/*障碍物区域下端点坐标值*/
	PerPointCloudDataTypeDef MinPoint;					/*障碍物区域最小点坐标值*/
	PerPointCloudDataTypeDef PixelBuffer[MAX_PIX_NUM];   /*保存障碍物所有像素点信息buffer*/
}ObstacleDataTypedef;

/*避障参数结构体*/
typedef struct
{
	bool avoidance_enable;          /*避障使能*/
	uint32_t avoidance_width;	    /*避障宽度*/
	uint32_t avoidance_height;      /*避障高度*/
	uint32_t avoidance_minDistance; /*避障安全距离*/
	uint32_t avoidance_mountHeight; /*安装高度*/
	uint32_t avoidance_pixelNumber; /*像素点阈值数量*/
	bool avoidance_alarmStatues;    /*报警状态*/
	GPIOOutConfTypeDef GpioOutConf; /*配置GPIO功能*/
}AvoidanceTypeDef;

/*结构体体封装结构体 用于数据的返回*/
typedef struct
{
	SimpleRoiDataTypeDef *simple_roi_data;	/*简单ROI数据包*/
	FullRoiDataTypeDef *full_roi_data;			/*完整ROI数据包*/
	DepthDataTypeDef *simple_depth_data;		/*简单深度图数据包*/
	DepthDataTypeDef *full_depth_data;			/*完整ROI数据包*/
	PointCloudDataTypeDef *point_cloud_data;	/*点云数据包*/
	ObstacleDataTypedef *Obstacle_data;			/*障碍物数据包*/
	uint8_t *Obstacle_frame_data_buff; 			/*用于存放障碍物数据包的缓冲区*/
}MeasureDataTypeDef;

/*通讯方式*/
typedef enum
{
	SYNC = 0x01,  						/*同步方式*/
	ASYNC = 0x02 						/*异步方式*/
}HPS3D_SynchronousTypedef;

/*传输类型*/
typedef enum
{
	TRANSPORT_USB = 0,					/*USB传输*/
	TRANSPORT_CAN,						/*CAN传输*/
	TRANSPORT_RS232,					/*RS232传输*/
	TRANSPORT_RS485,					/*RS485传输*/
	TRANSPORT_ETHERNET                  /*以太网传输*/
}TransportTypeDef;


/*handle*/
typedef struct
{
	char *DeviceName; 				/*当前所有可连接设备的名称(自动筛选)*/
	uint32_t DeviceFd;  				/*存放当前连接设备的文件描述符*/
	uint8_t DeviceAddr; 				/*存放当前连接设备的设备地址(也是帧ID)*/
	uint8_t ConnectionNumber;			/*设备连接编号*/
	HPS3D_SynchronousTypedef SyncMode;  /*同步或异步方式*/
	RunModeTypeDef RunMode;   			/*运行模式*/
	MeasureDataTypeDef MeasureData;     /*同步测量数据,当异步方式时测量结果不会保存在此(可通过观察者对其操作)*/
	RetPacketTypedef RetPacketType;     /*同步测量返回包类型,当异步方式时测量返回包类型结果不会保存在此(可通过观察者对其操作)*/
	OutPacketTypeDef OutputPacketType; 	/*输出数据包类型*/
	bool ConnectStatus;  	 			/*连接状态*/
	uint8_t RoiNumber;					/*保存当前设备支持的ROI数量*/
	uint8_t ThresholdNumber;			/*保存当前设备ROI支持的阈值数量*/
	uint8_t ViewAngleHorizontal;  		/*水平方向视场角*/
	uint8_t ViewAngleVertical;			/*垂直方向视场角*/
	struct sockaddr_in ServerAddr;	    /*服务器IP地址端口号*/
	TransportTypeDef TransportType;     /*当前传输类型*/
}HPS3D_HandleTypeDef;

/*光学参数*/
typedef struct
{
	bool enable;						/*光学参数使能（开启后，测量的深度数据为垂直距离）*/
	uint8_t viewing_angle_horiz;    	/*水平方向可视角*/
	uint8_t viewing_angle_vertical; 	/*垂直方向可视角*/
	uint8_t illum_angle_horiz;      	/*水平方向照明发射角*/
	uint8_t illum_angle_vertical;		/*垂直方向照明发射角*/
}OpticalParamConfTypeDef;

/*多机干扰的配置*/
typedef struct
{
	bool enable;						/*多机干扰检测使能*/
	uint32_t integ_time;				/*多机干扰检测积分时间*/
	uint16_t amplitude_threshold;		/*多机干扰检测阈值*/
	uint8_t capture_num;				/*多机干扰检测采样次数*/
	uint8_t number_check;				/*多机干扰检测采样次数检查*/
}InterferenceDetectConfTypeDef;


/*观察者订阅事件*/
typedef enum
{
	ISubject_Event_DataRecvd = 0x01,	/*数据记录事件*/
	ISubject_Event_DevConnect = 0x02,	/*设备连接事件*/
	ISubject_Event_DevDisconnect = 0x03 /*设备断开连接事件*/
}AsyncISubjectEvent;

/*观察者订阅事件结构体参数*/
typedef struct
{
	uint8_t ObserverID;  				/*用于区分观察者ID*/
	bool NotifyEnable;   				/*用于使能观察者*/
	AsyncISubjectEvent AsyncEvent; 		/*观察者订阅事件*/
	MeasureDataTypeDef MeasureData; 	/*用于存放测量结果*/
	RetPacketTypedef RetPacketType; 	/*用于区分返回包类型*/
}AsyncIObserver_t;

/*点云数据镜像*/
typedef enum
{
	MORROR_DISABLE = 0X0,    /*关闭镜像*/
	MIRROR_HORIZONTAL = 0X1, /*水平镜像*/
	MIRROR_VERTICLA = 0X2,   /*垂直镜像*/
}PointCloudImageMirrorTypeDef;

/**************************************函数接口*************************************/


/***********************************1.命令函数接口***********************************/
/**说明：在命令函数接口里，均有HPS3D_SetRunMode()函数，设置运行模式为暂停(RUN_IDLE)，才可发送命令。
 		在发送完命令后，记得开启原来的运行模式！！！
		（除HPS3D_SetRunMode本函数外）
 */

/**
 * @brief	设置测量模式
 * @param[in]   handle->DeviceAddr   设备地址
 * @param[in]   handle->DeviceFd     设备文件描述符fd
 * @param[in]   handle->RunMode 	 采集模式
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetRunMode(HPS3D_HandleTypeDef *handle);

/**
 * @brief	得到设备地址
 * @param[in]   handle->DeviceFd    设备文件描述符fd
 * @param[out]  handle->DeviceAddr  输出设备地址
 * @note
 * @retval	成功返回RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetDevAddr(HPS3D_HandleTypeDef *handle);

/**
 * @brief	设置设备地址
 * @param[in]	handle->DeviceAddr    原设备地址
 * @param[in]   handle->DeviceFd      设备文件描述符fd
 * @param[in]	new_addr     		  新设备地址
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetDevAddr(HPS3D_HandleTypeDef *handle, uint8_t new_addr);

/**
 * @brief	获取设备版本信息
 * @param[in]	handle->DeviceAddr    设备地址
 * @param[in]   handle->DeviceFd      设备文件描述符fd
 * @param[out]  version_t 		 	  输出设备版本信息
 * @param[out]	version_t.year		  年
 * @param[out]  version_t.month		  月
 * @param[out]  version_t.day		  日
 * @param[out]  version_t.major		  主版本号
 * @param[out]	version_t.minor		  次版本号
 * @param[out]	version_t.rev		  修订次数
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetDeviceVersion(HPS3D_HandleTypeDef *handle, Version_t *version_t);

/**
 * @brief	设定测量数据包类型，需在初始化完成前进行该配置
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]	handle->PacketType	   数据包类型选择输入
 * @note	默认为完整深度数据包
 * @see
 * @code
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetMeasurePacketType(MeasurePacketTypeDef type);
/**
 * @brief	获取测量数据包类型
 * @param[in]
 * @note	默认为完整深度数据包
 * @see
 * @code
 * @retval	返回类型枚举值
 */
extern MeasurePacketTypeDef HPS3D_GetMeasurePacketType(void);


/**
 * @brief	设定测量数据返回包类型(简单包或完整包)
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]   handle->DeviceFd       设备文件描述符fd
 * @param[in]	handle->PacketType	   数据包类型选择输入
 * 				-PACKET_FULL	       完整数据包（包含深度数据）
 *				-PACKET_SIMPLE		   简单数据包（不包含深度数据）
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetPacketType(HPS3D_HandleTypeDef *handle);

/**
 * @brief	获取数据包类型
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]   handle->DeviceFd       设备文件描述符fd
 * @param[out]	handle->PacketType     输出数据包的类型
 * 				-PACKET_FULL	       完整数据包（包含深度数据）
 *				-PACKET_SIMPLE		   简单数据包（不包含深度数据）
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetPacketType(HPS3D_HandleTypeDef *handle);

/**
 * @brief	保存到用户设定表
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]   handle->DeviceFd       设备文件描述符fd
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_ProfileSaveToCurrent(HPS3D_HandleTypeDef *handle);

/**
 * @brief	清除用户设置表
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]   handle->DeviceFd       设备文件描述符fd
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_ProfileClearCurrent(HPS3D_HandleTypeDef *handle);

/**
 * @brief	恢复出厂设置
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]   handle->DeviceFd       设备文件描述符fd
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_ProfileRestoreFactory(HPS3D_HandleTypeDef *handle);

/**
 * @brief	获得传输类型
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]   handle->DeviceFd       设备文件描述符fd
 * @param[out]	transport_type	 	   输出传输类型
 * 				-TRANSPORT_USB		   USB传输
 * 				-TRANSPORT_CAN		   CAN传输
 * 				-TRANSPORT_RS232       RS232传输
 * 				-TRANSPORT_RS485	   RS485传输
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetTransportType(HPS3D_HandleTypeDef *handle, TransportTypeDef *transport_type);

/**
 * @brief	选择ROI组
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]   handle->DeviceFd       设备文件描述符fd
 * @param[in]	group_id     		   ROI组选择输入
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SelectROIGroup(HPS3D_HandleTypeDef *handle, uint8_t group_id);

/**
 * @brief	获取当前ROI组ID
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]   handle->DeviceFd       设备文件描述符fd
 * @param[out]  group_id   			   输出当前ROI组ID
 * @note
 * @retval  成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetROIGroupID(HPS3D_HandleTypeDef *handle, uint8_t *group_id);

/**
 * @brief	设置ROI的警报类型
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]   handle->DeviceFd       设备文件描述符fd
 * @param[in]	group_id    	   	   ROI组选择输入
 * @param[in]	threshold_id 	   	   阈值选择输入
 * @param[in]	roi_alarm_type     	   警报类型选择输入
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetROIAlarmType(HPS3D_HandleTypeDef *handle, uint8_t roi_id, uint8_t threshold_id, ROIAlarmTypeDef roi_alarm_type);

/**
 * @brief	设置ROI的参考值类型
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]   handle->DeviceFd       设备文件描述符fd
 * @param[in]	roi_id       		   ROI组ID选择输入
 * @param[in]	threshold_id 		   阈值选择输入
 * @param[in]	type	     		   参考值类型选择输入
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetROIReferenceType(HPS3D_HandleTypeDef *handle, uint8_t roi_id, uint8_t threshold_id, ROIReferenceTypeDef ref_type);

/**
 * @brief	设定ROI区域
 * @param[in]	handle->DeviceAddr       设备地址
 * @param[in]   handle->DeviceFd         设备文件描述符fd
 * @param[in]	roi_conf.roi_id          ROI组ID选择输入
 * @param[in]	roi_conf.left_top_x		 左上角x坐标
 * @param[in]	roi_conf.left_top_y		 左上角y坐标
 * @param[in]	roi_conf.right_bottom_x  右下角x坐标
 * @param[in]   roi_conf.right_bottom_y  右下角y坐标
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetROIRegion(HPS3D_HandleTypeDef *handle, ROIConfTypeDef roi_conf);

/**
 * @brief	设置ROI使能
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]   handle->DeviceFd       设备文件描述符fd
 * @param[in]	roi_id          	   ROI组ID选择输入
 * @param[in]	en     				   使能
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetROIEnable(HPS3D_HandleTypeDef *handle, uint32_t roi_id, bool en);

/**
 * @brief	设置ROI阈值使能
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]   handle->DeviceFd       设备文件描述符fd
 * @param[in]	roi_id	               ROI ID选择输入
 * @param[in]	threshold_id 		   阈值选择输入
 * @param[in]	en     		 		   使能
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetROIThresholdEnable(HPS3D_HandleTypeDef *handle, uint32_t roi_id, uint32_t threshold_id, bool en);

/**
 * @brief	设置ROI阈值配置
 * @param[in]	handle->DeviceAddr     				设备地址
 * @param[in]   handle->DeviceFd            		设备文件描述符fd
 * @param[in]	roi_id       						ROI ID选择输入
 * @param[in]	threshold_id 						阈值id选择输入
 * @param[in]   pix_num_threshold   				超过阈值的像素点数
 * @param[in]	hysteresis_conf.threshold_value		阈值
 * @param[in]	hysteresis_conf.hysteresis  		迟滞（死区）大小
 * @param[in]	hysteresis_conf.positive			比较器极性，true:正向比较, false：反向比较
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetROIThresholdConf(HPS3D_HandleTypeDef *handle, uint32_t roi_id, uint32_t threshold_id, uint16_t pix_num_threshold, HysteresisSingleConfTypeDef hysteresis_conf);

/**
 * @brief	获取当前设备支持的ROI数量和阈值数量
 * @param[in]	handle->DeviceAddr     设备地址
 * @param[in]   handle->DeviceFd       设备文件描述符fd
 * @param[out]	roi_number      	   ROI 的数量
 * @param[out]	threshold_number 	   阈值的数量
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetNumberOfROI(HPS3D_HandleTypeDef *handle, uint8_t *roi_number, uint8_t *threshold_number);

/**
 * @brief	获取指定的ROI配置
 * @param[in]	handle->DeviceAddr     									设备地址
 * @param[in]   handle->DeviceFd            							设备文件描述符fd
 * @param[in]   roi_id  		       									指定ROI
 * @param[out]  roi_conf			   									输出配置
 * @param[out]	roi_conf.roi_id											ROI的ID
 * @param[out]	roi_conf.enable											ROI使能
 * @param[out]	roi_conf.left_top_x										左上角x坐标
 * @param[out]	roi_conf.left_top_y										左上角y坐标
 * @param[out]	roi_conf.right_bottom_x									右上角x坐标
 * @param[out]	roi_conf.right_bottom_y									右上角y坐标
 *
 * （三组阈值输出）
 * @param[out]	roi_conf.ref_type[threshold_id]							ROI的参考值类型
 * @param[out]	roi_conf.alarm_type[threshold_id]						ROI的阈值警报类型
 * @param[out]	roi_conf.pixel_number_threshold[threshold_id]			超过阈值的像素点数
 * @param[out]	roi_conf.hysteresis_conf[threshold_id].threshold_id		阈值ID
 * @param[out]	roi_conf.hysteresis_conf[threshold_id].hysteresis		迟滞大小
 * @param[out]	roi_conf.hysteresis_conf[threshold_id].threshold_value	阈值
 * @param[out]	roi_conf.hysteresis_conf[threshold_id].positive			阈值极性
 * @param[out]	roi_conf.hysteresis_conf[threshold_id].enable			阈值使能
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetROIConfById(HPS3D_HandleTypeDef *handle, uint8_t roi_id, ROIConfTypeDef *roi_conf);

/**
 * @brief	设置指定的GPIO输出端口的配置
 * @param[in]	handle->DeviceAddr       设备地址
 * @param[in]   handle->DeviceFd         设备文件描述符fd
 * @param[in]	gpio_out_conf 		     GPIO配置
 * @param[in]	gpio_out_conf.gpio	     GPIO输出口选择
 * @param[in]	gpio_out_conf.function   GPIO输出功能设置
 * @param[in]	gpio_out_conf.polarity   GPIO输出极性
 * @note        gpio_out_conf：只能配置IO输出
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetGPIOOut(HPS3D_HandleTypeDef *handle, GPIOOutConfTypeDef gpio_out_conf);

/**
 * @brief	获取指定GPIO输出端口的配置
 * @param[in]	handle->DeviceAddr       设备地址
 * @param[in]   handle->DeviceFd         设备文件描述符fd
 * @param[in]	gpio_out_conf->gpio	     GPIO端口号选择
 * @param[out]	gpio_out_conf    	     GPIO输出配置
 * @param[out]	gpio_out_conf.function   GPIO输出功能设置
 * @param[out]	gpio_out_conf.polarity   GPIO输出极性
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetGPIOOutConf(HPS3D_HandleTypeDef *handle, GPIOOutConfTypeDef *gpio_out_conf);

/**
 * @brief	设置指定的GPIO输入端口的配置
 * @param[in]	handle->DeviceAddr      设备地址
 * @param[in]   handle->DeviceFd        设备文件描述符fd
 * @param[in]	gpio_in_conf 		    GPIO配置
 * @param[in]	gpio_in_conf.gpio	    GPIO输入口选择
 * @param[in]	gpio_in_conf.function   GPIO输入功能设置
 * @param[in]	gpio_in_conf.polarity   GPIO输入极性
 * @note		gpio_in_conf：只能配置IO输入
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetGPIOIn(HPS3D_HandleTypeDef *handle, GPIOInConfTypeDef gpio_in_conf);

/**
 * @brief	获取指定GPIO输入端口的配置
 * @param[in]	handle->DeviceAddr      设备地址
 * @param[in]   handle->DeviceFd        设备文件描述符fd
 * @param[in]	gpio		  		    GPIO端口号选择
 * @param[out]	gpio_in_conf   	  	    获取GPIO配置的结构体指针
 * @param[out]	gpio_in_conf.function   GPIO输入功能设置
 * @param[out]	gpio_in_conf.polarity   GPIO输入极性
 * @note
 * @retval	 成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetGPIOInConf(HPS3D_HandleTypeDef *handle, GPIOInConfTypeDef *gpio_in_conf);

/**
 * @brief	设置HDR模式
 * @param[in]	handle->DeviceAddr     	设备地址
 * @param[in]   handle->DeviceFd        设备文件fd
 * @param[in]	hdr_mode   		 		输入HDR的模式
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetHDRMode(HPS3D_HandleTypeDef *handle, HDRModeTypeDef hdr_mode);

/**
 * @brief	设置HDR
 * @param[in]	handle->DeviceAddr     					设备地址
 * @param[in]   handle->DeviceFd        				设备文件描述符fd
 * @param[in]	hdr_conf    		   					输入HDR的配置
 * @param[in]	hdr_conf.hdr_mode						HDR模式选择
 * 1、选择AUTO-HDR：
 * @param[in]	hdr_conf.qualtity_overexposed			AUTO-HDR曝光幅值
 * @param[in]	hdr_conf.qualtity_overexposed_serious	AUTO-HDR过度曝光幅值
 * @param[in]	hdr_conf.qualtity_weak					AUTO-HDR信号弱幅值
 * @param[in]	hdr_conf.qualtity_weak_serious			AUTO-HDR信号极弱幅值
 * 2、选择SIMPLE-HDR：
 * @param[in]	hdr_conf.simple_hdr_max_integration		SIMPLE-HDR最大积分时间
 * @param[in]	hdr_conf.simple_hdr_min_integration		SIMPLE-HDR最小积分时间
 * 3、选择SUPER-HDR
 * @param[in]	hdr_conf.super_hdr_frame_number			SUPER-HDR合成帧数
 * @param[in]	hdr_conf.super_hdr_max_integration		SUPER-HDR最大积分时间
 * 4、选择HDR-DISABLE
 * @param[in]	hdr_conf.hdr_disable_integration_time	HDR-DISABLE手动积分时间
 * @note		1、hdr_mode必须设置成HDR_DISABLE、AUTO_HDR、SUPER_HDR、	SIMPLE_HDR,否则返回RET_ERROR;
 * 			    2、其余配置按照HDRConf结构体里面的数据类型配置
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetHDRConfig(HPS3D_HandleTypeDef *handle, HDRConf hdr_conf);

/**
 * @brief	获取HDR配置
 * @param[in]	handle->DeviceAddr     					设备地址
 * @param[in]   handle->DeviceFd        				设备文件描述符fd
 * @param[out]	hdr_conf	  		   					获取HDR配置
 * @param[out]	hdr_conf.hdr_mode						HDR模式选择
 * @param[out]	hdr_conf.qualtity_overexposed			AUTO-HDR曝光幅值
 * @param[out]	hdr_conf.qualtity_overexposed_serious	AUTO-HDR过度曝光幅值
 * @param[out]	hdr_conf.qualtity_weak					AUTO-HDR信号弱幅值
 * @param[out]	hdr_conf.qualtity_weak_serious			AUTO-HDR信号极弱幅值
 * @param[out]	hdr_conf.simple_hdr_max_integration		SIMPLE-HDR最大积分时间
 * @param[out]	hdr_conf.simple_hdr_min_integration		SIMPLE-HDR最小积分时间
 * @param[out]	hdr_conf.super_hdr_frame_number			SUPER-HDR合成帧数
 * @param[out]	hdr_conf.super_hdr_max_integration		SUPER-HDR最大积分时间
 * @param[out]	hdr_conf.hdr_disable_integration_time	HDR-DISABLE手动积分时间
 * @note
 * @retval	 成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetHDRConfig(HPS3D_HandleTypeDef *handle, HDRConf *hdr_conf);

/**
 * @brief	设置距离滤波器类型
 * @param[in]	handle->DeviceAddr     	  		设备地址
 * @param[in]   handle->DeviceFd          		设备文件描述符fd
 * @param[in]	distance_filter_conf 	  		滤波器类型
 * 				-DISTANCE_FILTER_DISABLE  		距离滤波器不使能
 * 				-DISTANCE_FILTER_SIMPLE_KALMAN	简单卡尔曼滤波器
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetDistanceFilterType(HPS3D_HandleTypeDef *handle, DistanceFilterTypeDef distance_filter_conf);

/**
 * @brief	配置距离滤波器
 * @param[in]	handle->DeviceAddr     	  				设备地址
 * @param[in]   handle->DeviceFd          				设备文件描述符fd
 * @param[in]	distance_filter_conf	  				距离滤波器的配置
 * @param[in]	distance_filter_conf.kalman_K			距离滤波器的比例系数K
 * @param[in]	distance_filter_conf.num_check			距离滤波器阈值检查帧数
 * @param[in]	distance_filter_conf.kalman_threshold	距离滤波器噪声阈值
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetSimpleKalman(HPS3D_HandleTypeDef *handle, DistanceFilterConfTypeDef distance_filter_conf);

/**
 * @brief	获取距离滤波器配置
 * @param[in]	handle->DeviceAddr     	  				设备地址
 * @param[in]   handle->DeviceFd          				设备文件描述符fd
 * @param[out]	distance_filter_conf   	  				距离滤波器的结构体指针
 * @param[out]	distance_filter_conf.filter_type		距离滤波器的类型
 * @param[out]	distance_filter_conf.kalman_K			距离滤波器的比例系数K
 * @param[out]	distance_filter_conf.num_check			距离滤波器阈值检查帧数
 * @param[out]	distance_filter_conf.kalman_threshold	距离滤波器噪声阈值
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetDistanceFilterConf(HPS3D_HandleTypeDef *handle, DistanceFilterConfTypeDef *distance_filter_conf);

/**
 * @brief	设置平滑滤波器
 * @param[in]	handle->DeviceAddr     	  	设备地址
 * @param[in]   handle->DeviceFd          	设备文件描述符fd
 * @param[in]	smooth_filter_conf	  	  	平滑滤波器的设置
 * @param[in]	smooth_filter_conf.type		平滑滤波器的类型
 * @param[in]	smooth_filter_conf.arg1		平滑滤波器的滤波参数
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetSmoothFilter(HPS3D_HandleTypeDef *handle, SmoothFilterConfTypeDef smooth_filter_conf);

/**
 * @brief	获取平滑滤波器的配置
 * @param[in]	handle->DeviceAddr     	  	设备地址
 * @param[in]   handle->DeviceFd          	设备文件描述符fd
 * @param[out]	smooth_filter_conf	  	  	平滑滤波器配置的结构体指针
 * @param[out]	smooth_filter_conf.type		平滑滤波器的类型
 * @param[out]	smooth_filter_conf.arg1		平滑滤波器的滤波参数
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetSmoothFilterConf(HPS3D_HandleTypeDef *handle, SmoothFilterConfTypeDef *smooth_filter_conf);

/**
 * @brief	设定光学参数使能
 * @param[in]	handle->DeviceAddr     	  设备地址
 * @param[in]   handle->DeviceFd          设备文件描述符fd
 * @param[in]	en			  			  使能信号
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetOpticalEnable(HPS3D_HandleTypeDef *handle, bool en);

/**
 * @brief	获取光学参数
 * @param[in]	handle->DeviceAddr     	 		 			设备地址
 * @param[in]   handle->DeviceFd          					设备文件描述符fd
 * @param[out]	optical_param_conf	 	  					获取光学参数的结构体指针
 * @param[out]	optical_param_conf.enable					光学参数使能
 * @param[out]	optical_param_conf.viewing_angle_horiz		光学参数水平方向可视角
 * @param[out]	optical_param_conf.viewing_angle_vertical	光学参数垂直方向可视角
 * @param[out]	optical_param_conf.illum_angle_horiz		光学参数水平方向照明发射角
 * @param[out]	optical_param_conf.illum_angle_vertical		光学参数垂直方向照明发射角
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetOpticalParamConf(HPS3D_HandleTypeDef *handle, OpticalParamConfTypeDef *optical_param_conf);

/**
* @brief	设置距离补偿
* @param[in]	handle->DeviceAddr     	  设备地址
* @param[in]    handle->DeviceFd          设备文件描述符fd
* @param[in]	offset		  			  补偿距离
* @note
* @retval	成功返回 RET_OK
*/
extern RET_StatusTypeDef HPS3D_SetDistanceOffset(HPS3D_HandleTypeDef *handle, int16_t offset);

/**
* @brief	获得距离补偿
* @param[in]	handle->DeviceAddr     	  设备地址
* @param[in]    handle->DeviceFd          设备文件描述符fd
* @param[out]	offset		  			  输出距离补偿
* @note
* @retval	成功返回 RET_OK
*/
extern RET_StatusTypeDef HPS3D_GetDistanceOffset(HPS3D_HandleTypeDef *handle, int16_t *offset);

/**
 * @brief	设置多机干扰检测使能
 * @param[in]	handle->DeviceAddr     	  设备地址
 * @param[in]   handle->DeviceFd          设备文件描述符fd
 * @param[in]	en		  	 			  使能信号
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetInterferenceDetectEn(HPS3D_HandleTypeDef *handle, bool en);

/**
 * @brief	设置多机干扰检测积分时间
 * @param[in]	handle->DeviceAddr     	  设备地址
 * @param[in]   handle->DeviceFd          设备文件描述符fd
 * @param[in]	us		  	  			  积分时间
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetInterferenceDetectIntegTime(HPS3D_HandleTypeDef *handle, uint32_t us);

/**
 * @brief	设置多机干扰检测阈值
 * @param[in]	handle->DeviceAddr     	  设备地址
 * @param[in]   handle->DeviceFd          设备文件描述符fd
 * @param[in]	thre		  			  阈值
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetInterferenceDetectAmplitudeThreshold(HPS3D_HandleTypeDef *handle, uint16_t thre);

/**
 * @brief	设置多机干扰检测采样次数
 * @param[in]	handle->DeviceAddr     	  设备地址
 * @param[in]   handle->DeviceFd          设备文件描述符fd
 * @param[in]	capture_number  		  采样次数
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetInterferenceDetectCaptureNumber(HPS3D_HandleTypeDef *handle, uint8_t capture_number);

/**
 * @brief	设置多机干扰检测采样次数检查
 * @param[in]	handle->DeviceAddr     	  设备地址
 * @param[in]   handle->DeviceFd          设备文件描述符fd
 * @param[in]	capture_number_check   	  采样次数
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetInterferenceDetectNumberCheck(HPS3D_HandleTypeDef *handle, uint8_t capture_number_check);

/**
 * @brief	获得多机干扰的配置
 * @param[in]	handle->DeviceAddr     	  						设备地址
 * @param[in]   handle->DeviceFd          						设备文件描述符fd
 * @param[out]	interference_detect_conf  						获得多机干扰配置的结构体指针
 * @param[out]	interference_detect_conf.enable					多机干扰检测使能
 * @param[out]	interference_detect_conf.integ_time				多机干扰检测积分时间
 * @param[out]	interference_detect_conf.amplitude_threshold	多机干扰检测阈值
 * @param[out]	interference_detect_conf.capture_num			多机干扰检测采样次数
 * @param[out]	interference_detect_conf.number_check			多机干扰检测采样次数检查
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetInterferenceDetectConf(HPS3D_HandleTypeDef *handle, InterferenceDetectConfTypeDef *interference_detect_conf);

/**
 * @brief	设定安装角度变换使能
 * @param[in]	handle->DeviceAddr     	  设备地址
 * @param[in]   handle->DeviceFd          设备文件描述符fd
 * @param[in]	en		      			  使能信号
 * @note
 * @retval	成功返回 RET_OK
 */
/*extern RET_StatusTypeDef HPS3D_SetMountingAngleEnable(HPS3D_HandleTypeDef *handle, bool en);*/ /*此接口不再使用，采用以下接口替换*/

/**
 * @brief	设定安装角度变换参数
 * @param[in]	handle->DeviceAddr     	  					设备地址
 * @param[in]   handle->DeviceFd          					设备文件描述符fd
 * @param[in]	mounting_angle_param_conf 					安装角度变换参数的配置
 * @param[in]	mounting_angle_param_conf.angle_vertical	垂直方向安装角度（°）
 * @param[in]	mounting_angle_param_conf.height			相对于地面的安装高度
 * @note
 * @retval	返回设定安装角度变换参数的结果，成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetMountingAngleParamConf(HPS3D_HandleTypeDef *handle, MountingAngleParamTypeDef mounting_angle_param_conf);

/**
 * @brief	获取安装角度变换参数
 * @param[in]	handle->DeviceAddr     	  					设备地址
 * @param[in]   handle->DeviceFd          					设备文件描述符fd
 * @param[out]	mounting_angle_param_conf 					获得安装角度变换参数的结构体指针
 * @param[out]	mounting_angle_param_conf.enable			安装角度变换参数使能
 * @param[out]	mounting_angle_param_conf.angle_vertical	垂直方向安装角度（°）
 * @param[out]	mounting_angle_param_conf.height			相对于地面的安装高度(mm)
 * @note
 * @retval	返回获取安装角度变换参数的结果，成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_GetMountingParamConf(HPS3D_HandleTypeDef *handle, MountingAngleParamTypeDef *mounting_angle_param_conf);



/*************************************2.集成函数接口**********************************/

/**
 * @brief	获取目录下指定前缀文件(自动寻找设备)
 * @param[in]	dirPath 设备文件根目录
 * @param[in]   prefix  设备文件名前缀
 * @param[out]  fileName 用于保存当前当前目录下寻找到的设备
 * @note		例：n = HPS3D_GetDeviceList("/dev/","ttyACM",fileName);
 * @retval	返回获取成功的数量 0表示失败
 */
extern uint32_t HPS3D_GetDeviceList(char *dirPath,char *prefix,char fileName[DEV_NUM][DEV_NAME_SIZE]);

/**
 * @brief	设备连接
 * @param[in]	handle->DeviceName  	设备名路径
 * @param[out]	handle->DeviceFd		设备文件描述符fd
 * @param[out]	handle->ConnectStatus	连接状态true
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_Connect(HPS3D_HandleTypeDef *handle);

/**
 * @brief	断开连接
 * @param[in]	handle->DeviceFd		设备文件描述符fd
 * @param[out]	handle->ConnectStatus	连接状态false
 * @note	函数执行的操作：
 * 			1.设置运行模式停止
 * 			2.close(fd)
 * 			3.ConnectStatus = false
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_DisConnect(HPS3D_HandleTypeDef *handle);


/**
 * @brief	设备初始化
 * @param[in]	handle->mode				运行模式
 * @param[in]	handle->SyncMode			通讯模式
 * @param[out]	handle->DeviceAddr			输出设备地址
 * @param[out]	handle->OpticalEnable    	输出光学使能信号true or false
 * @note	函数执行的操作：
 * 			1.创建线程,创建读串口数据线程
 * 			2.先设置运行模式为停止模式（发命令时需要关闭运行模式）	HPS3D_SetRunMode(...)
 * 			3.发送获得设备地址命令	HPS3D_GetDevAddr(...)	[out]handle->DeviceAddr
 * 			4.发送获得光学参数使能命令	HPS3D_GetOpticalParamConf(...)	[out]handle->OpticalEnable
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_ConfigInit(HPS3D_HandleTypeDef *handle);


/**
 * @brief	设置ROI的阈值
 * @param[in]	handle->DeviceAddr     									设备地址
 * @param[in]	handle->DeviceFd										设备文件描述符fd
 * @param[in]	threshold_id		  									阈值id
 * @param[in]	roi_conf			   									ROI配置结构体
 * @param[in]	roi_conf.roi_id											ROI的ID
 * @param[in]	roi_conf.ref_type[threshold_id]							ROI的参考值类型
 * @param[in]	roi_conf.alarm_type[threshold_id]						ROI的阈值警报类型
 * @param[in]	roi_conf.pixel_number_threshold[threshold_id]			超过阈值的像素点数
 * @param[in]	roi_conf.hysteresis_conf[threshold_id].hysteresis		单点迟滞大小
 * @param[in]	roi_conf.hysteresis_conf[threshold_id].threshold_value	单点阈值
 * @param[in]	roi_conf.hysteresis_conf[threshold_id].positive			单点阈值极性
 * @param[in]	roi_conf.hysteresis_conf[threshold_id].enable			单点阈值使能
 * @note		函数执行的操作：
 * 				1.先设置运行模式为停止模式（发命令时需要关闭运行模式）	HPS3D_SetRunMode(...)
 * 				2.发送设置ROI阈值配置命令	HPS3D_SetROIThresholdConf(...)
 * 				3.发送设置ROI的参考值类型命令	HPS3D_SetROIReferenceType(...)
 * 				4.发送设置ROI的警报类型命令		HPS3D_SetROIAlarmType(...)
 * 				5.发送设置ROI阈值使能命令	HPS3D_SetROIThresholdEnable(...)
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetThreshold(HPS3D_HandleTypeDef *handle, uint8_t threshold_id, ROIConfTypeDef roi_conf);

/**
 * @brief	设置单个ROI
 * @param[in]	handle->DeviceAddr     									设备地址
 * @param[in]	handle->DeviceFd										设备文件描述符fd
 * @param[in]   roi_conf 			   									ROI的设置结构体
 * @param[in]	roi_conf.roi_id											ROI的ID
 * @param[in]	roi_conf.enable											ROI使能
 * @param[in]	roi_conf.left_top_x										左上角x坐标
 * @param[in]	roi_conf.left_top_y										左上角y坐标
 * @param[in]	roi_conf.right_bottom_x									右上角x坐标
 * @param[in]	roi_conf.right_bottom_y									右上角y坐标
 *
 * 设置三组阈值
 * @param[in]	roi_conf.ref_type[threshold_id]							ROI的参考值类型
 * @param[in]	roi_conf.alarm_type[threshold_id]						ROI的阈值警报类型
 * @param[in]	roi_conf.pixel_number_threshold[threshold_id]			超过阈值的像素点数
 * @param[in]	roi_conf.hysteresis_conf[threshold_id].roi_id			单点阈值属于哪个ROI
 * @param[in]	roi_conf.hysteresis_conf[threshold_id].hysteresis		单点迟滞大小
 * @param[in]	roi_conf.hysteresis_conf[threshold_id].threshold_value	单点阈值
 * @param[in]	roi_conf.hysteresis_conf[threshold_id].positive			单点阈值极性
 * @param[in]	roi_conf.hysteresis_conf[threshold_id].enable			单点阈值使能
 *
 * @param[in]   gpio_out_conf		  	 								GPIO配置结构体
 * @param[in]	gpio_out_conf.gpio	   									GPIO输出口选择
 * @param[in]	gpio_out_conf.function 									GPIO输出功能设置
 * @param[in]	gpio_out_conf.polarity 									GPIO输出极性
 * @note		gpio_out_conf：只能配置IO输出
 *				函数执行的操作：
 *				1.先设置运行模式为停止模式（发命令时需要关闭运行模式）	HPS3D_SetRunMode(...)
 *				2.发送设置ROI使能命令	HPS3D_SetROIEnable(...)
 *				3.发送设定ROI区域命令	HPS3D_SetROIRegion(...)
 *				4.发送设置ROI的阈值命令（三组阈值都设置）	HPS3D_SetThreshold(...1/2/3)
 *				5.发送设置指定的GPIO输出端口的配置命令	HPS3D_SetGPIOOut(...)
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetSingleRoi(HPS3D_HandleTypeDef *handle, ROIConfTypeDef roi_conf, GPIOOutConfTypeDef gpio_out_conf);

/**
 * @brief	异步模式(连续测量模式) 添加观察者
 * @param[in]	Observer_t               		观察者结构体
 * @param[in]	Observer_t->ObserverFunAddr     观察者函数地址
 * @param[in]   Observer_t->NotifyEnable 		观察者使能
 * @param[in]   Observer_t->AsyncEvent  		观察者通知事件
 * @param[in]   Observer_t->ObserverID   		观察者ID
 * @note 在退出观察者模式时必须调用移除观察者函数进行内存释放
 * @retval 成功返回RET_OK
 */
extern RET_StatusTypeDef HPS3D_AddObserver(void * (*fun)(HPS3D_HandleTypeDef *,AsyncIObserver_t *),HPS3D_HandleTypeDef *handle,AsyncIObserver_t *Observer_t);

/**
 * @brief	异步模式(连续测量模式) 移除观察者
 * @param[in]	Observer_t             		  观察者结构体
 * @param[in]	Observer_t->ObserverFunAddr   观察者函数地址
 * @param[in]   Observer_t->ObserverID 		  观察者ID
 * @param[in]   Observer_t->AsyncEvent 		  观察者通知事件
 * @note
 * @retval 成功返回RET_OK
 */
extern RET_StatusTypeDef HPS3D_RemoveObserver(AsyncIObserver_t *Observer_t);

/**
 * @brief	设备卸载与资源回收(线程退出与资源释放)
 * @param[in]	handle->DeviceAddr     设备地址
 * @note	函数执行的操作：
 * 			1.HPS3D_DisConnect(...)
 * 			2.如果handle->SyncMode == ASYNC或handle->RunMode == RUN_CONTINUOUS，则等待线程退出
 * @retval 成功返回RET_OK
 */
extern RET_StatusTypeDef HPS3D_RemoveDevice(HPS3D_HandleTypeDef *handle);

/**
 * @brief		设置debug使能
 * @param[in]	en				使能信号（默认开启）
 * @note
 * @retval	 成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetDebugEnable(bool en);

/**
 * @brief		获得debug使能
 * @param
 * @note
 * @retval	 成功返回 true or false
 */
extern bool HPS3D_GetDebugEnable(void);

/**
 * @brief		接收回调函数的地址
 * @param[in]	void *Call_Back     接收回调函数地址   回调函数为void *fun(uint8_t *str, uint16_t *str_len){...}
 * @param[out]	返回给回调函数str和strlen
 * @note
 * @retval	 成功返回 RET_OK
 */
RET_StatusTypeDef HPS3D_SetDebugFunc(void (*Call_Back)(char *str));

/**
 * @brief	设置点云数据转换使能
 * @param[in]	en     使能信号
 * @note
 * @retval	成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SetPointCloudEn(bool en);

/**
 * @brief	得到点云数据转换使能信号
 * @param
 * @note
 * @retval	true or false
 */
extern bool HPS3D_GetPointCloudEn(void);

/**
 * @brief		基本解析数据转换为点云数据输出
 * @param[in]	 MeasureData.full_roi_data/MeasureData.full_depth_data		解析的数据（结构体）
 * @param[in]	 RetPacketType												解析的数据类型
 * @param[out]  MeasureData.point_cloud_data								可以调用点云数据转换使能接口，设置输出的数据是否为点云数据
 * @note
 * @see
 * @code
 *
 * @retval	 成功返回 RET_OK
 */
RET_StatusTypeDef HPS3D_BaseToPointCloud(MeasureDataTypeDef *MeasureData, RetPacketTypedef RetPacketType);

/**
 * @brief		将所有的ROI进行拼接，拼接成一张160x60的深度图
 * @param[in]	MeasureData			需要保存的测量数据
 * @param[in]   RetPacketType       测量数据的类型,必须是FULL_ROI_PACKET类型
 * @param[out]	distance     		拼接完的深度图160x60
 * @note
 * @retval	 成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_RoiDepthCompound(MeasureDataTypeDef *MeasureData,RetPacketTypedef RetPacketType, uint16_t *distance);


/**
 * @brief		单次测量
 * @param[in]	handle->DeviceAddr	设备地址
 * @param[out]	handle->RetPacketType	测量数据的类型
 * @param[out]	handle->MeasureData		需要保存的测量数据
 * @note   该方式为同步测量，即调用此函数后理解得到测量返回值
 * @see
 * @code
 *
 * @retval	 成功返回 RET_OK
 */
extern RET_StatusTypeDef HPS3D_SingleMeasurement(HPS3D_HandleTypeDef *handle);

/**
 * @brief		初始化障碍物提取参数
 * @param[in]	Conf	配置障碍物参数
 * @note
 * @see
 * @code
 *
 * @retval	 成功返回 RET_OK
 */
extern ObstacleConfigTypedef HPS3D_GetObstacleConfigInit(void);

/**
 * @brief		获取障碍物提取配置参数
 * @param
 * @note
 * @see
 * @code
 * @retval	 返回障碍物配置参数信息
 */
extern RET_StatusTypeDef HPS3D_ObstacleConfigInit(ObstacleConfigTypedef Conf);

/**
 * @brief		设置障碍物像素点个数阈值
 * @param
 * @note
 * @see
 * @code
 * @retval none
 */
extern void HPS3D_SetObstaclePixelNumberThreshold(uint32_t pixel_num_thr);
/**
 * @brief		获取障碍物像素点个数阈值
 * @param
 * @note
 * @see
 * @code
 * @retval  返回数量值
 */
extern uint32_t HPS3D_GetObstaclePixelNumberThreshold(void);


/**
 * @brief		设置障碍物提取阈值偏置
 * @param
 * @note
 * @see
 * @code
 * @retval  返回空
 */
extern void HPS3D_SetThresholdOffset(int32_t thr_offset);

/**
 * @brief		获取障碍物提取阈值偏置
 * @param
 * @note
 * @see
 * @code
 * @retval  阈值
 */
extern int32_t HPS3D_GetThresholdOffset(void);


/**
 * @brief		获取SDK版本号
 * @param
 * @note
 * @see
 * @code
 * @retval	 版本信息
 */
extern Version_t HPS3D_GetSDKVersion(void);



/* brief		将特殊测量输出值转换为指定特殊值参数配置
 * param[in]	enable 使能设置
 * param[in]    value  特殊测量结果重新赋值
 * @note
 * @see
 * @code
 *
 * @retval	 返回状态值
 */
extern RET_StatusTypeDef HPS3D_ConfigSpecialMeasurementValue(bool enable,uint16_t value);


/* brief		设置边缘噪声滤除使能
 * param[in]	enable： true使能，false关闭
 * @note
 * @see
 * @code
 *
 * @retval	 返回状态值
 */
extern RET_StatusTypeDef HPS3D_SetEdgeDetectionEnable(bool en);

/* brief		获取边缘噪声滤除使能
 * param[in]
 * @note
 * @see
 * @code
 *
 * @retval	 返回状态值
 */
extern bool HPS3D_GetEdgeDetectionEnable(void);


/* brief		设置边缘噪声阈值
 * param[in]	enable： true使能，false关闭
 * @note
 * @see
 * @code
 *
 * @retval	 返回状态值
 */
extern RET_StatusTypeDef HPS3D_SetEdgeDetectionValue(int32_t threshold_value);

/* brief		获取边缘噪声阈值
 * param[in]
 * @note
 * @see
 * @code
 *
 * @retval	 返回状态值
 */
extern int32_t HPS3D_GetEdgeDetectionValue(void);

/**
  * @brief	保存点云数据为ply格式文件
  * @param[in] filename  文件名
  * @param[in] point_cloud_data 测量结果中的电源数据
  * @note
  * @see
  * @code
  * @retval 返回状态值
  */
/**/
extern RET_StatusTypeDef HPS3D_SavePlyFile(char *filename,PointCloudDataTypeDef point_cloud_data);

/**
  * @brief	钻货架方案(3IO版本通过IO输出报警值)
  * @param[in] handle 用于配置GPIO输出;
  * @param[in] MeasureData 测量数据
  * @param[in/out] AvoidConf  避障参数配置
  * @note
  * @see
  * @code
  * @retval	成功返回RET_OK
  */
extern RET_StatusTypeDef HPS3D_ObstacleAvoidance(HPS3D_HandleTypeDef *handle,MeasureDataTypeDef *MeasureData,AvoidanceTypeDef *AvoidConf);

/**
  * @brief	设置点云数据镜像
  * @param[in] 镜像方向
  * @note
  * @see
  * @code
  * @retval	None
  */
extern RET_StatusTypeDef HPS3D_SetPointCloudMirrorType(PointCloudImageMirrorTypeDef type);
/**
  * @brief	获取点云数据镜像
  * @param[in] 镜像方向
  * @note
  * @see
  * @code
  * @retval	None
  */
extern PointCloudImageMirrorTypeDef HPS3D_GetPointCloudMirrorType(void);

/**
  * @brief	设置服务器信息
  * @param[in]	handle 设备相关结构体
  * @param[in]  服务器信息
  * @note
  * @see
  * @code
  * @retval	成功返回RET_OK
  */
extern RET_StatusTypeDef HPS3D_SetEthernetServerInfo(HPS3D_HandleTypeDef *handle,uint8_t *serverIP,uint16_t serverPort);

/**
  * @brief	重置服务器IP
  * @param[in]	handle 设备相关结构体
  * @param[in]  serverIP 服务器IP
  * @param[in]  serverPort 服务器端口
  * @param[in]  netmask 服务器子网掩码
  * @param[in]  gateway 服务器默认网关
  * @note 例serverIP[4] = {192,168,0,10};
  *         netMask[4] = {255,255,255,0};
  *         geteway[4] = {192,168,0,1};
  *         serverPort = 12345;
  * @see
  * @code
  * @retval	成功返回RET_OK
  */
RET_StatusTypeDef HPS3D_ConfigEthernet(HPS3D_HandleTypeDef *handle,uint8_t *serverIP,uint16_t serverPort,uint8_t *netMask,uint8_t *geteway);

/**
  * @brief	多设备自动连接（不超过DEV_NUM = 10）
  * @param[in] handle 保存设备参数的handle数组
  * @note
  * @see
  * @code
  * @retval	返回连接成功的数量
  */
extern uint8_t HPS3D_AutoConnectAndInitConfigDevice(HPS3D_HandleTypeDef *handle);



#ifdef __cplusplus
}
#endif

#endif /* API_H_ */
