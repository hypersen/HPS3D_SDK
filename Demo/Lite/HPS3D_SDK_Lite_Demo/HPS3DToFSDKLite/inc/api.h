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
* \date 2018年11月29日 上午11:43:31
* \license private & classified
*---------------------------------------------------------------------
* Remark: This project is still under construction.
*======================================================================
* Change History:
*---------------------------------------------------------------------
* <Date>			| <Version>	| <Author>			| <Description>
*---------------------------------------------------------------------
* 2018年11月29日			| V1.0.0	| Kevin				| Create file
*======================================================================
* Detailed Notes:
*---------------------------------------------------------------------
* <Version>		| <Description>
*---------------------------------------------------------------------
* V1.0.0		| TODO
*---------------------------------------------------------------------

**********************************************************************/
#ifndef HPS3DTOFSDKLITE_INC_API_H_
#define HPS3DTOFSDKLITE_INC_API_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*类型的定义*/
typedef float float32_t;
typedef double float64_t;

/*	分辨率	*/
#define 	ROI_NUM 		(20)
#define		RES_WIDTH		(160)
#define		RES_HEIGHT		(60)
#define		PIXEL_WIDTH_SIZE		(20)	/*微米*/
#define		PIXEL_HEIGHT_SIZE		(20)	/*微米*/
#define		MAX_PIX_NUM 	(RES_WIDTH * RES_HEIGHT)

/*返回数据包的报头和报尾*/
#define PACKET_HEAD1  0xf5
#define PACKET_HEAD2  0x5f
#define PACKET_TAIL1  0x5f
#define PACKET_TAIL2  0xf5

/*无效数据点*/
#define	 	LOW_AMPLITUDE   （65300） 		/*振幅太低*/
#define	  SATURATION 			（65400）    	/*饱和位饱和*/
#define	 	ADC_OVERFLOW  	（65500）  		/*ADC溢出*/
#define	 	INVALID_DATA 		（65530）   		/*无效数据*/


/*函数返回的结果*/
typedef enum
{
	RET_OK = 0x01,
	RET_ERROR = 0x02,
	RET_BUSY = 0x03
}RET_StatusTypeDef;



/*简单数据包的ROI数据*/
typedef struct
{
	uint8_t group_id;
	uint8_t id;/*存储roi id*/
	uint16_t amplitude;/*平均幅值*/
	uint16_t valid_amplitude;/*平均有效幅值*/
	uint16_t distance_average;/*平均距离值*/
	uint16_t distance_max;/*最大距离值*/
	uint16_t distance_min;/*最小距离值*/
	uint16_t dist_max_x;
	uint16_t dist_max_y;
	uint16_t dist_min_x;
	uint16_t dist_min_y;
	uint16_t saturation_count;/*饱和像素点数*/
	uint8_t threshold_state;/*当前测量值是否超出阈值:bit0:zone0, bit1:zone1, bit2:zone2*/
	uint16_t out_of_threshold_pix_num[3];/*用于调试，不公开 [0]:超过thresold 0的像素点数,[1]:...,[2]:...*/
	uint16_t frame_cnt;
}SimpleROIDataTypeDef;

/*Auto HDR调节模式*/
typedef enum
{
	HDR_DISABLE = 0,
	AUTO_HDR,
	SUPER_HDR,
	SIMPLE_HDR
}HDRModeTypeDef;

/*HDR配置*/
typedef struct
{
	HDRModeTypeDef hdr_mode;
	uint8_t super_hdr_frame_number;
	uint32_t super_hdr_max_integration;
	float32_t qualtity_overexposed;
	float32_t qualtity_overexposed_serious;
	float32_t qualtity_weak;
	float32_t qualtity_weak_serious;
	float32_t int_adjust_overexposed_ratio;
	float32_t int_adjust_overexposed_ratio2;/*曝光稍微高了，比例要比int_adjust_overexposed_ratio要小一些*/
	float32_t int_adjust_weak_ratio;
	float32_t int_adjust_weak_ratio2;
	uint8_t hdr_divisor;/*hdr两个积分时间的倍数*/
	uint32_t simple_hdr_max_integration;
	uint32_t simple_hdr_min_integration;
}HDRConfTypeDef;


/*输出数据类型选择*/
typedef enum
{
	MinOfOutputDataType = 0,
	OUTPUT_POINTCLOUD = 0,
	OUTPUT_AMPLITUDE,
	OUTPUT_RAW_DCS,
	OUTPUT_DISTANCE,
	OUTPUT_DISTANCE_AND_AMPLITUDE,
	OUTPUT_GRAYSCALE,
	NumberOfOutputDataType,
}OutputDataTypeDef;

/*解析数据包的类型*/
typedef enum
{
	NULL_PACKET = 0x00,
	SIMPLE_ROI_PACKET = 0x01,
	FULL_ROI_PACKET,
	FULL_DEPTH_PACKET,
	SIMPLE_DEPTH_PACKET,
	SYSTEM_ERROR
}RetPacketTypedef;


/*简单包数据*/
typedef struct
{
	uint16_t distance_average;
	uint16_t amplitude_average;
	uint16_t amplitude_average_whole;
	uint16_t amplitude_low_count;
	uint16_t saturation_count;
	uint16_t distance_max;
	uint16_t distance_min;
	int16_t temperature;/*温度值*/
	uint16_t frame_cnt;
	uint16_t interference_num;/*受干扰的像素点，debug*/
}DepthDataTypeDef;


/*联合体封装 用于测量数据的返回*/
typedef union
{
	SimpleROIDataTypeDef simple_roi_data[ROI_NUM];
	DepthDataTypeDef simple_depth_data;
}MeasureDataTypeDef;

/*特定意义的RID*/
typedef enum
{
	RID_SIMPLE_ROI_PACKET = 0x16,
	RID_SIMPLE_DEPTH_PACKET = 0x19,
}SpecialRIDTypeDef;

/*设备版本*/
typedef struct
{
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t major;
	uint8_t minor;
	uint8_t rev;
}Version_t;

/*运行模式选择*/
typedef enum
{
	MinOfRunModeType = 0,
	RUN_IDLE = 0,
	RUN_SINGLE_SHOT,
	RUN_CONTINUOUS,
	NumberOfRunModeType
}RunModeTypeDef;

/*设置数据包的类型*/
typedef enum
{
	PACKET_FULL = 0,
	PACKET_SIMPLE,
	PACKET_UNKNOWN = 255,
}PacketTypeDef;


/*ROI的阈值警报类型*/
typedef enum
{
	ROI_ALARM_DISABLE = 0,   /*关闭ROI区域警报，仅输出ROI区域的信息和数据，用户自己判断处理*/
	ROI_ALARM_GPIO       /*ROI区域警报类型为GPIO OUT电平输出*/
}ROIAlarmTypeDef;

/*单点的迟滞配置*/
typedef struct
{
	uint8_t roi_id;  /*当前阈值属于哪个roi*/
	uint32_t threshold_value; /*阈值的值*/
	uint32_t hysteresis; /*迟滞大小*/
	bool enable;
	bool positive;/*true:正向比较，如果输入值大于阈值则返回True
							false:反向比较，如果输入值小于阈值则返回False*/
}HysteresisSingleConfTypeDef;

/*ROI的参考值类型*/
typedef enum
{
	ROI_REF_DIST_AVR = 1,/*ROI区域的距离平均值作为参考值*/
	ROI_REF_DIST_MIN,/*ROI区域的距离最小值作为参考值*/
	ROI_REF_DIST_MAX,/*ROI区域的距离最大值作为参考值*/
	ROI_REF_SAT_COUNT,/*ROI区域的饱和像素点数量作为参考值*/
	ROI_REF_AMPLITUDE,/*ROI区域的幅值平均值作为参考值*/
	ROI_REF_VAILD_AMPLITUDE,/*ROI区域的有效幅值平均值作为参考值*/
	ROI_REF_THRESHOLD_PIX_NUM/*超过设定阈值的像素点数，相比最大值比较和最小值比较具有更高的可靠性*/
}ROIReferenceTypeDef;

/*ROI配置的结构体*/
 typedef struct
{
	uint16_t left_top_x;
	uint16_t left_top_y;
	uint16_t right_bottom_x;
	uint16_t right_bottom_y;
	HysteresisSingleConfTypeDef hysteresis_conf[3];
	uint8_t roi_id;/*ROI的ID*/
	bool enable;/*使能标识*/
	ROIReferenceTypeDef ref_type[3];/*与hysteresis_conf一一对应*/
	ROIAlarmTypeDef alarm_type[3];/*与hysteresis_conf一一对应*/
	uint16_t pixel_number_threshold[3];/*超过阈值的像素点数阈值,与hysteresis_conf一一对应*/
}ROIConfTypeDef;


/*平滑滤波器的类型*/
typedef enum
{
	SMOOTH_FILTER_DISABLE = 0,
	SMOOTH_FILTER_AVERAGE = 1,
	SMOOTH_FILTER_GAUSS
}SmoothFilterTypeDef;

/*平滑滤波器的配置结构体*/
typedef struct
{
	SmoothFilterTypeDef type;
	uint32_t arg1;
}SmoothFilterConfTypeDef;

/*GPIO配置的相关定义*/
typedef enum
{
	GPOUT_FUNC_DISABLE = 0,
	GPOUT_FUNC_ROI_THRESHOLD0_ALARM,
	GPOUT_FUNC_ROI_THRESHOLD1_ALARM,
	GPOUT_FUNC_ROI_THRESHOLD2_ALARM
}GPOutFunctionTypeDef;

typedef enum
{
	GPIN_FUNC_DISABLE = 0,
	GPIN_FUNC_CAPTURE   /*开启测量*/
}GPInFunctionTypeDef;

typedef enum
{
	GPIO_POLARITY_LOW = 0,
	GPIO_POLARITY_HIGH
}GPIOPolarityTypeDef;

typedef enum
{
	GPIN_1 = 1,
	GPOUT_1 = 10
}GPIOTypeDef;

typedef struct
{
	GPIOTypeDef gpio;
	GPIOPolarityTypeDef polarity;
	GPOutFunctionTypeDef function;
}GPIOOutConfTypeDef;

typedef struct
{
	GPIOTypeDef gpio;
	GPIOPolarityTypeDef polarity;
	GPInFunctionTypeDef function;
}GPIOInConfTypeDef;


/*滤波器类型*/
typedef enum
{
	DISTANCE_FILTER_DISABLE = 0,
	DISTANCE_FILTER_SIMPLE_KALMAN
}DistanceFilterTypeDef;

typedef struct
{
	DistanceFilterTypeDef filter_type;
	float32_t kalman_K; /*for simple kalman*/
	uint32_t num_check;
	uint32_t kalman_threshold;
}DistanceFilterConfTypeDef;



/*HDR配置*/
typedef struct
{
	HDRModeTypeDef hdr_mode;
	float32_t qualtity_overexposed;
	float32_t qualtity_overexposed_serious;
	float32_t qualtity_weak;
	float32_t qualtity_weak_serious;
	uint32_t simple_hdr_max_integration;
	uint32_t simple_hdr_min_integration;
	uint8_t super_hdr_frame_number;
	uint32_t super_hdr_max_integration;
	uint32_t hdr_disable_integration_time;/*us*/
}HDRConf;

/*光学参数*/
typedef struct
{
	bool enable;
	uint8_t viewing_angle_horiz;    /*水平方向可视角*/
	uint8_t viewing_angle_vertical; /*垂直方向可视角*/
	uint8_t illum_angle_horiz;      /*水平方向照明发射角*/
	uint8_t illum_angle_vertical;	/*垂直方向照明发射角*/
}OpticalParamConfTypeDef;
 
 
/*函数声明*/
RET_StatusTypeDef HPS3D_MeasureDataParse(uint8_t *buf,MeasureDataTypeDef *MeasureData, RetPacketTypedef *RetPacketType);
RET_StatusTypeDef HPS3D_GetDevAddr(uint8_t *devAddr);
RET_StatusTypeDef HPS3D_SetDevAddr(uint8_t devAddr, uint8_t new_addr);
RET_StatusTypeDef HPS3D_GetDeviceVersion(uint8_t devAddr, Version_t *version_t);

RET_StatusTypeDef HPS3D_GetFactoryInfo(uint8_t devAddr, uint8_t *info);
RET_StatusTypeDef HPS3D_SetRunMode(uint8_t devAddr, RunModeTypeDef mode);

RET_StatusTypeDef HPS3D_SetOutputDataType(uint8_t devAddr, OutputDataTypeDef type);
OutputDataTypeDef HPS3D_GetOutputDataType(uint8_t devAddr);

RET_StatusTypeDef HPS3D_SetIntegrationTime(uint8_t devAddr, uint32_t us);
int32_t HPS3D_GetIntegTime(uint8_t devAddr);

RET_StatusTypeDef HPS3D_ProfileSaveToCurrent(uint8_t devAddr);
RET_StatusTypeDef HPS3D_ProfileClearCurrent(uint8_t devAddr);
RET_StatusTypeDef HPS3D_ProfileRestoreFactory(uint8_t devAddr);

RET_StatusTypeDef HPS3D_SelectROIGroup(uint8_t devAddr, uint8_t group_id);
int8_t HPS3D_GetROIGroupID(uint8_t devAddr);
RET_StatusTypeDef HPS3D_SetROIAlarmType(uint8_t devAddr, uint8_t roi_id, uint8_t threshold_id, ROIAlarmTypeDef type);

RET_StatusTypeDef HPS3D_SetPacketType(uint8_t devAddr, PacketTypeDef type);
PacketTypeDef HPS3D_GetPacketType(uint8_t devAddr);

RET_StatusTypeDef HPS3D_SetROIReferenceType(uint8_t devAddr, uint8_t roi_id, uint8_t threshold_id, ROIReferenceTypeDef type);
RET_StatusTypeDef HPS3D_SetROIRegion(uint8_t devAddr, uint8_t roi_id, uint16_t left_top_x, uint16_t left_top_y, uint16_t right_bottom_x, uint16_t right_bottom_y);
RET_StatusTypeDef HPS3D_SetROIEnable(uint8_t devAddr, uint32_t id, bool en);
RET_StatusTypeDef HPS3D_SetROIThresholdEnable(uint8_t devAddr, uint32_t roi_id, uint32_t threshold_id, bool en);
RET_StatusTypeDef HPS3D_SetROIThresholdConf(uint8_t devAddr, uint32_t roi_id, uint32_t threshold_id, uint32_t threshold, uint32_t hysteresis, bool positive, uint16_t pix_num_threshold);
RET_StatusTypeDef HPS3D_GetNumberOfROI(uint8_t devAddr, uint8_t *roi_number, uint8_t *threshold_number);
RET_StatusTypeDef HPS3D_GetROIConfById(uint8_t devAddr, uint32_t id, ROIConfTypeDef *conf);

RET_StatusTypeDef HPS3D_SetHDRMode(uint8_t devAddr, HDRConfTypeDef conf);
RET_StatusTypeDef HPS3D_SetAutoHDRConfig(uint8_t devAddr, HDRConfTypeDef conf);
RET_StatusTypeDef HPS3D_SetSuperHDRConfig(uint8_t devAddr, HDRConfTypeDef conf);
RET_StatusTypeDef HPS3D_SetSimpleHDRConfig(uint8_t devAddr, HDRConfTypeDef conf);
RET_StatusTypeDef HPS3D_GetHDRConfig(uint8_t devAddr, HDRConfTypeDef *conf);

RET_StatusTypeDef HPS3D_SetGPIOOut(uint8_t devAddr, GPIOTypeDef gpio, GPOutFunctionTypeDef func, GPIOPolarityTypeDef polarity);
RET_StatusTypeDef HPS3D_GetGPIOOutConf(uint8_t devAddr, GPIOTypeDef gpio, GPIOOutConfTypeDef *gpio_conf);


RET_StatusTypeDef HPS3D_SetOpticalEnable(uint8_t devAddr, bool en);
RET_StatusTypeDef HPS3D_SetOpticalParamConf(uint8_t devAddr, OpticalParamConfTypeDef conf);
RET_StatusTypeDef HPS3D_GetOpticalParamConf(uint8_t devAddr, OpticalParamConfTypeDef *conf);

RET_StatusTypeDef HPS3D_SetDistanceOffset(uint8_t devAddr, int16_t offset);
int16_t HPS3D_GetDistanceOffset(uint8_t devAddr);

RET_StatusTypeDef HPS3D_SetGPIOIn(uint8_t devAddr, GPIOTypeDef gpio, GPInFunctionTypeDef func, GPIOPolarityTypeDef polarity);
RET_StatusTypeDef HPS3D_GetGPIOInConf(uint8_t devAddr, GPIOTypeDef gpio, GPIOInConfTypeDef *gpio_conf);

RET_StatusTypeDef HPS3D_SetDistanceFilterType(uint8_t devAddr, DistanceFilterTypeDef type);
RET_StatusTypeDef HPS3D_SetSimpleKalman(uint8_t devAddr, DistanceFilterConfTypeDef conf);
RET_StatusTypeDef HPS3D_GetDistanceFilterConf(uint8_t devAddr, DistanceFilterConfTypeDef *conf);
Version_t HPS3D_GetSDKVersion(void);
RET_StatusTypeDef HPS3D_Initialize(uint8_t *dev_addr);

#endif /* API_H_ */
