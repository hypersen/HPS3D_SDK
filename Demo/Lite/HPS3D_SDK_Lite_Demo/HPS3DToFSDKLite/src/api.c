/**********************************************************************
* COPYRIGHT NOTICE - HYPERSEN TECHNOLOGY
*
* Copyright (c) 2018, Hypersen Technology, Inc.
*
* All rights reserved.
*
*======================================================================
* \file api.c
* \brief TODO
* \author Joker
* \email Joker_Wu@hypersen.com
* \version 1.0.0
* \date 2018年11月29日 下午3:07:24
* \license private & classified
*---------------------------------------------------------------------
* Remark: This project is still under construction.
*======================================================================
* Change History:
*---------------------------------------------------------------------
* <Date>			| <Version>	| <Author>			| <Description>
*---------------------------------------------------------------------
* 2018年11月29日			| V1.0.0	| Joker				| Create file
*======================================================================
* Detailed Notes:
*---------------------------------------------------------------------
* <Version>		| <Description>
*---------------------------------------------------------------------
* V1.0.0		| TODO
*---------------------------------------------------------------------

**********************************************************************/
#include "HPS3DToFSDKLite/inc/api.h"
#include "HPS3DToFSDKLite/inc/crc.h"
#include "HPS3DToFSDKLite/inc/hal.h"

/*	SDK支持的固件版本	*/
#define SUPPORT_FOR_MAJOR		(1)
#define	SUPPORT_FOR_MINOR		(7)

/*发送命令的包头*/
#define PACK_HEAD1  0xF5
#define PACK_HEAD2  0x0A

/*数据解析用到的解包长度*/
#define ROI_EXTEND_INFO_LEN  32/*字节*/
#define ROI_HEADER_INFO_LEN  24
#define FULL_DISTANCE_EXTEND_INFO_LEN  24/*字节*/

/*数据包的命令定义*/
 #define CMD_GET_DEVICVERSION 0xa0
 #define CMD_FACTORY_INFO 0xa1
 #define CMD_OUTPUT_DATA_TYPE 0xa2
 #define CMD_SET_RUN_MODE 0xa3
 #define CMD_INTEGRATION_TIME 0xa4
 #define CMD_OPMODE 0xa5
 #define CMD_CALIBRATION 0xa6
 #define CMD_DLL_DELAY_TEST 0xa7
 #define CMD_CORRECT_EN 0xa8
 #define CMD_SAVE_PROFILE 0xa9
 #define CMD_CLEAR_PROFILE 0xaa
 #define CMD_RESTORE_FACTORY 0xab
 #define CMD_ROI 0xac
 #define CMD_HDR_CONFIG 0xad
 #define CMD_HDR_INTEGRATION_TIME 0xae
 #define CMD_SMOOTH_FILTER 0xaf
 #define CMD_GPIO_OUT 0xb0
 #define CMD_FACTORY_MISC 0xb1
 #define CMD_MULT_DEVICE_INTERFERENCE 0xb2
 #define CMD_OPTICAL_PARAM 0xb3
 #define CMD_BAD_PIXELS 0xb5
 #define CMD_DISTANCE_OFFSET 0xb6
 #define CMD_HARDWARE_INFO 0xb7
 #define CMD_GPIO_IN 0xb8
 #define CMD_TRANSPORT 0xb9
 #define CMD_DEV_ADDR 0xba
 #define CMD_PACKET_TYPE 0xbb
 #define CMD_DISTANCE_FILTER 0xbc
 #define CMD_INTERFERENCE_CONF 0xbd

static RET_StatusTypeDef CRC_VerifyPacket(uint8_t *buf,uint32_t buf_len);
static RET_StatusTypeDef HAL_SimpleCommunication(uint8_t *write_buff,uint32_t write_len, uint8_t *ret_buff,uint32_t timeout_ms);
static RET_StatusTypeDef Cmd_CreatePack(uint8_t *packbuf, uint8_t cmd, uint8_t *args, uint32_t args_len);
static uint32_t Cmd_UnPack(uint8_t *buf, uint8_t cmd, uint8_t *ret_pack);
static RET_StatusTypeDef CRC_VerifyPacket(uint8_t *buf,uint32_t buf_len);
/**
  * @brief 获取API版本号
  * @note
  * @see
  * @code
  * @retval	返回API版本号
  */
Version_t HPS3D_GetSDKVersion(void)
{
	Version_t ver;
	ver.year = 18;
	ver.month = 12;
	ver.day = 3;
	ver.major = 1;
	ver.minor = 0;
	ver.rev = 0;
	
	return ver;
}

/**
  * @brief 初始化设备
  * @param[out] dev_addr	返回当前的设备地址
  * @note
  * @see
  * @code
  * @retval	读取成功返回RET_OK
  */
RET_StatusTypeDef HPS3D_Initialize(uint8_t *dev_addr)
{
	Version_t dev_ver;
	RET_StatusTypeDef ret = RET_OK;
	
	do
	{
		HPS3D_SetRunMode(0xff, RUN_IDLE);
		Delay_Ms(1000);
		
		if(RET_OK != HPS3D_GetDevAddr(dev_addr))
		{
			ret = RET_ERROR;
			break;
		}
		
		if(RET_OK != HPS3D_GetDeviceVersion(*dev_addr, &dev_ver))
		{
			ret = RET_ERROR;
			break;
		}
		/*检查当前API版本是否支持此设备的固件*/
		if(SUPPORT_FOR_MAJOR != dev_ver.major || SUPPORT_FOR_MINOR != dev_ver.minor)
		{
			ret = RET_ERROR;
			break;
		}
		/*进行一些初始化*/
		if(RET_OK != HPS3D_SetPacketType(0, PACKET_SIMPLE))
		{
			ret = RET_ERROR;
			break;
		}
		
		
	}while(0);
	
	return ret;
}

/**
  * @brief 解析测量数据包
  * @param[in]	buf:原始数据
  * @param[out] MeasureData：测量数据
	* @param[out] RetPacketType：测量数据类型
  * @note
  * @see
  * @code
  * @retval	解析成功返回RET_OK
  */
RET_StatusTypeDef HPS3D_MeasureDataParse(uint8_t *buf, MeasureDataTypeDef *MeasureData, RetPacketTypedef *RetPacketType)
{
	/*uint8_t dev_addr = 0;*/
	RET_StatusTypeDef ret = RET_OK;
	uint32_t size = 0;
	uint8_t rid = 0;  /*命令Rid返回值*/
	uint16_t tag = 0;
	uint8_t RoiNumber = 0;
	uint32_t frame_cnt = 0;
/*	uint16_t dummy = 0;*/
	*RetPacketType = NULL_PACKET; /*默认幅值为空类型*/
	
	do
	{
		/*验证报头 第0和1个字节为报头*/  
		if ((buf[0] != PACKET_HEAD1) || (buf[1] != PACKET_HEAD2))
		{
			ret = RET_ERROR;
			break;
		}
		/*得到数据长度 第2和3个字节为报文长度*/
		size = (uint32_t)( (buf[2] << 0) | (buf[3] << 8) );
		/*进行数据包CRC16校验*/
		ret = CRC_VerifyPacket(buf,size + 4);
		if(ret != RET_OK)
		{
			break;
		}
		/*得到设备地址与rid*/
		//dev_addr = buf[4];
		rid = buf[4 + 1];
		
		/*进行简单数据包进行解析*/
		switch(rid)
		{
			case RID_SIMPLE_ROI_PACKET: /*简单ROI数据包解析*/
				*RetPacketType = SIMPLE_ROI_PACKET;
				tag = (uint16_t)(buf[4 + 3] * 256 + buf[4 + 2]);
				RoiNumber = tag & 0xff;
				frame_cnt = (uint32_t)((buf[4 + 7] << 24) | (buf[4 + 6]) << 16 | (buf[4 + 5] << 8) | (buf[4 + 4] << 0));
				for(int i = 0;i < RoiNumber; i++)
				{
					MeasureData->simple_roi_data[i].group_id = (uint8_t)(tag >> 8);
					MeasureData->simple_roi_data[i].frame_cnt = frame_cnt;
					MeasureData->simple_roi_data[i].id = (uint8_t)(buf[i*ROI_EXTEND_INFO_LEN+ROI_HEADER_INFO_LEN+1+2+4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 0 + 2 + 4]);
					MeasureData->simple_roi_data[i].amplitude = (uint16_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 3 + 2 + 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 2 + 2 + 4]);
					MeasureData->simple_roi_data[i].valid_amplitude = (uint16_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 5 + 2 + 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 4 + 2 + 4]);
					MeasureData->simple_roi_data[i].distance_average = (uint16_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 7 + 2+ 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 6 + 2 + 4]);
					MeasureData->simple_roi_data[i].distance_max = (uint16_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 9 + 2 + 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 8 + 2 + 4]);
					MeasureData->simple_roi_data[i].distance_min = (uint16_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 11 + 2+ 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 10 + 2 + 4]);
					MeasureData->simple_roi_data[i].saturation_count = (uint16_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 13 + 2 + 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 12 + 2 + 4]);
					MeasureData->simple_roi_data[i].threshold_state = (uint8_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 15 + 2 + 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 14 + 2 + 4]);
					MeasureData->simple_roi_data[i].dist_max_x = (uint16_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 17 + 2 + 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 16 + 2 + 4]);
					MeasureData->simple_roi_data[i].dist_max_y = (uint16_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 19 + 2 + 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 18 + 2 + 4]);
					MeasureData->simple_roi_data[i].dist_min_x = (uint16_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 21 + 2 + 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 20 + 2 + 4]);
					MeasureData->simple_roi_data[i].dist_min_y = (uint16_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 23 + 2 + 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 22 + 2 + 4]);
					MeasureData->simple_roi_data[i].out_of_threshold_pix_num[0] = (uint16_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 25 + 2 + 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 24 + 2 + 4]);
					MeasureData->simple_roi_data[i].out_of_threshold_pix_num[1] = (uint16_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 27 + 2 + 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 26 + 2 + 4]);
					MeasureData->simple_roi_data[i].out_of_threshold_pix_num[2] = (uint16_t)(buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 29 + 2 + 4] * 256 + buf[i * ROI_EXTEND_INFO_LEN + ROI_HEADER_INFO_LEN + 28 + 2 + 4]);
					
				}
				break;
			case RID_SIMPLE_DEPTH_PACKET: /*完整ROI数据解析*/
				*RetPacketType = SIMPLE_DEPTH_PACKET;
				/*dummy = (uint16_t)(buf[3 + 4] * 256 + buf[2 + 4]); */
				MeasureData->simple_depth_data.distance_average = (uint16_t)(buf[5 + 4] * 256 + buf[4 + 4]);
				MeasureData->simple_depth_data.amplitude_average = (uint16_t)(buf[7 + 4] * 256 + buf[6 + 4]);
				MeasureData->simple_depth_data.amplitude_average_whole = (uint16_t)(buf[9 + 4] * 256 + buf[8 + 4]);
				MeasureData->simple_depth_data.amplitude_low_count = (uint16_t)(buf[11 + 4] * 256 + buf[10 + 4]);
				MeasureData->simple_depth_data.saturation_count = (uint16_t)(buf[13 + 4] * 256 + buf[12 + 4]);
				MeasureData->simple_depth_data.distance_max = (uint16_t)(buf[15 + 4] * 256 + buf[14 + 4]);
				MeasureData->simple_depth_data.distance_min = (uint16_t)(buf[17 + 4] * 256 + buf[16 + 4]);
				MeasureData->simple_depth_data.frame_cnt = (uint32_t)((buf[21 + 4] << 24) | (buf[20 + 4]) << 16 | (buf[19 + 4] << 8) | (buf[18 + 4] << 0));
				MeasureData->simple_depth_data.interference_num = (uint16_t)(buf[23 + 4] * 256 + buf[22 + 4]);
				MeasureData->simple_depth_data.temperature = (int16_t)(buf[25 + 4] * 256 + buf[24 + 4]);								
				break;		
			default:
				ret = RET_ERROR;
				break;
		}
			
	}while(0);
	
	return ret;
}

/**
  * @brief	 与传感器进行一次简单的命令通信（此函数仅获得返回包，不进行校验）
  * @param[in]	write_buff:写入数据存放的buffer
  * 			write_len:写入数据的长度
  * @param[out] ret_buff：返回数据的buffer
  * @note
  * @see
  * @code
  * @retval	读取成功返回RET_OK
  */
RET_StatusTypeDef HAL_SimpleCommunication(uint8_t *write_buff,uint32_t write_len, uint8_t *ret_buff,uint32_t timeout_ms)
{
	RET_StatusTypeDef	ret = RET_OK;
	uint32_t ret_len = 0;

	do
	{
		/*串口写数据*/
		Uart_Write(write_buff, write_len, 100);
		/*读两个字节的报头和报文长度,此处调用读函数 保存在ret_buff[0] 与 ret_buff[1]*/
		Uart_Read(ret_buff, 4, 100);
		
		/*校验报头*/
		if(ret_buff[0] != PACKET_HEAD1 || ret_buff[1] != PACKET_HEAD2)
		{
			ret = RET_ERROR;
			break;
		}	
		/*得到返回包长度*/
		ret_len = ((ret_buff[3]<<8) |  ret_buff[2]);
		
		/*读取报文长度(包含crc校验值与报尾) 读取ret_len字节,保存在以ret_buff[4]开始的空间内*/
		Uart_Read(ret_buff+4, ret_len, timeout_ms);
			
	}while(0);
	
	return ret;
}

/**
 * @brief	命令数据打包
 * @param[out]	packbuf[]    数据包
 * @param[in]	cmd	         命令
 * @param[in]	args[]       参数(包含设备地址)
 * @param[in]	args_len     args[]的长度
 * @note
 * @see
 * @code
 *
 * @retval	返回打包结果
 */
RET_StatusTypeDef Cmd_CreatePack(uint8_t *packbuf, uint8_t cmd, uint8_t *args, uint32_t args_len)
{
	uint16_t crc_val = 0;
	uint32_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	int32_t i = 0;
	do
	{
		packbuf[indx++] = PACK_HEAD1;
		packbuf[indx++] = PACK_HEAD2;
		packbuf[indx++] = (uint8_t)(1 + args_len + 2);
		packbuf[indx++] = cmd;
		for(i = 0;i<args_len;i++)
		{
			packbuf[indx++] = args[i];
		}
		crc_val = crc16_cal(packbuf + 3, indx - 3);

		packbuf[indx++] = (crc_val>>0)&0xff;
		packbuf[indx++] = (crc_val>>8)&0xff;

	}while(0);

	return ret;
}



/**
 * @brief	对命令返回包进行解析
 * @param[in]	buf[]       完整命令包
 * @param[in]   cmd   	    相应命令的RID
 * @param[out]	ret_pack[]  解析后数据包 （去掉包头2 + 报文长度2 + 设备地址1 + rid 1 + crc 2 + 报尾2）
 * @note
 * @see
 * @code
 *
 * @retval	返回 解析完后包的长度
 */
uint32_t Cmd_UnPack(uint8_t *buf, uint8_t cmd, uint8_t *ret_pack)
{
	RET_StatusTypeDef ret = RET_OK;
	uint32_t pack_len = 0;
	uint32_t retpack_len = 0;
	/*uint8_t addr;*/
	int32_t rid;
	uint32_t i;

	do
	{
		 /*验证报头*/
		if ( ( buf[0] == PACKET_HEAD1 ) && ( buf[1] == PACKET_HEAD2 ) )
		{
			/*得到报文长度*/
			pack_len = (uint32_t)((buf[3] << 8) | (buf[2] << 0));
			/*开始CRC校验*/
			ret = CRC_VerifyPacket(buf, pack_len + 4);
			if( ret != RET_OK )
			{
				retpack_len = 0;
				break;
			}

			/*完整的命令返回包：报头2 + 报文长度2 + 设备地址1 + rid 1 + 数据字段 + crc 2 + 报尾2*/
			/*响应的设备地址*/
			/*addr = buf[4];*/
			
			/*返回命令包的rid*/
			rid = buf[5];
			
			/*验证命令返回RID*/
			if(cmd == rid)
			{
				/*去掉报头2 + 报文长度2 + 设备地址1 + rid 1 + crc 2 + 报尾2*/
				for(i = 0 ; i < pack_len - 6 ; i++ )
				{
					ret_pack[i] = buf[ 4 + 2 + i ];
				}
				retpack_len = pack_len - 2 - 4;
			}
			else
			{
				retpack_len = 0;
				break;
			}
		}
	}while(0);

	return retpack_len;
}


/**
  * @brief	devAddr 得到设备地址
  * @param[out]    返回设备地址
  * @note
  * @see
  * @code
  *
  * @retval	成功返回RET_OK
  */
RET_StatusTypeDef HPS3D_GetDevAddr(uint8_t *devAddr)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = 0xff;/*广播地址*/
		args[indx++] = 0x02;
		ret = Cmd_CreatePack(packbuf, CMD_DEV_ADDR, args, indx);
		if( ret != RET_OK )
		{
			break;
		}

		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}
		retback_len = Cmd_UnPack(retbuf, CMD_DEV_ADDR, ret_pack);
		if( retback_len > 0 )
		{
			*devAddr = ret_pack[0];
		}
		else
		{		
			ret = RET_ERROR;
			break;
		}

	}while(0);

	return ret;
}


 /**
  * @brief	设置设备地址
  * @param[in]	old_addr      原设备地址
  * @param[in]	new_addr     新设备地址
  * @note
  * @see
  * @code
  *
  * @retval	返回设置设备地址的结果，成功返回 RET_OK
  */
 RET_StatusTypeDef HPS3D_SetDevAddr(uint8_t old_addr, uint8_t new_addr)
 {
 	uint8_t args[20];
 	/*用于记录参数的个数*/
 	uint8_t indx = 0;
 	RET_StatusTypeDef ret = RET_OK;
 	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

 	do
	{
		args[indx++] = old_addr;
		args[indx++] = 0x01;
		args[indx++] = new_addr;
		ret = Cmd_CreatePack(packbuf, CMD_DEV_ADDR, args, indx);
		if( ret != RET_OK )
		{
			break;
		}

		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}
		retback_len = Cmd_UnPack(retbuf, CMD_DEV_ADDR, ret_pack);
		if( retback_len <= 0 )
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
 }

 
 /**
 * @brief	获取设备版本信息
 * @param[in]	devAddr      设备地址
 * @param[out]  version_t    输出设备版本信息
 * @note
 * @see
 * @code
 *
 * @retval	返回设备版本的结果，成功返回 RET_OK
 */
RET_StatusTypeDef HPS3D_GetDeviceVersion(uint8_t devAddr, Version_t *version_t)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		ret = Cmd_CreatePack(packbuf, CMD_GET_DEVICVERSION, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_GET_DEVICVERSION, ret_pack);
		if( retback_len > 0 )
		{
			version_t->year = ret_pack[0];
			version_t->month = ret_pack[1];
			version_t->day = ret_pack[2];
			version_t->major = ret_pack[3];
			version_t->minor = ret_pack[4];
			version_t->rev = ret_pack[5];
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
* @brief	设置运行模式
* @param[in]	devAddr       设备地址
* @param[in]	mode         	运行模式
* @note	如果当前相机处于RUN_CONTINUOUS状态，返回值不可信。
* @see
* @code
*
* @retval	返回设置运行模式的结果，成功返回 RET_OK
*/
 RET_StatusTypeDef HPS3D_SetRunMode(uint8_t devAddr, RunModeTypeDef mode)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x01;/*写*/
		args[indx++] = (uint8_t)mode;
		ret = Cmd_CreatePack(packbuf, CMD_SET_RUN_MODE, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}
		retback_len = Cmd_UnPack(retbuf, CMD_SET_RUN_MODE, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}

	}while(0);

	return ret;
}


/**
 * @brief	设置数据输出类型
 * @param[in]	devAddr       设备地址
 * @param[in]	type         数据输出类型
 * @note
 * @see
 * @code
 *
 * @retval	返回设置数据输出类型的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetOutputDataType(uint8_t devAddr, OutputDataTypeDef type)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x01;/*写*/
		args[indx++] = (uint8_t)type;
		ret = Cmd_CreatePack(packbuf, CMD_OUTPUT_DATA_TYPE, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_OUTPUT_DATA_TYPE, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	设置积分时间
 * @param[in]	devAddr       设备地址
 * @param[in]	us	         	积分时间,单位微秒
 * @note
 * @see
 * @code
 *
 * @retval	返回设置积分时间的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetIntegrationTime(uint8_t devAddr, uint32_t us)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x01;/*写*/
		args[indx++] = (uint8_t)(us >> 0);
		args[indx++] = (uint8_t)(us >> 8);
		args[indx++] = (uint8_t)(us >> 16);
		args[indx++] = (uint8_t)(us >> 24);
		ret = Cmd_CreatePack(packbuf, CMD_INTEGRATION_TIME, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_INTEGRATION_TIME, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	获得积分时间
 * @param[in]	devAddr     设备地址
 * @note
 * @see
 * @code
 *
 * @retval	返回积分时间
 */
 int32_t HPS3D_GetIntegTime(uint8_t devAddr)
 {
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;
	int32_t time = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x02;/*读*/

		ret = Cmd_CreatePack(packbuf, CMD_INTEGRATION_TIME, args, indx);
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		if( ret != RET_OK )
		{
			time = -1;
			break;
		}

		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			time = -1;
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_INTEGRATION_TIME, ret_pack);
		if( retback_len > 0 )
		{
			time = ((ret_pack[0] << 0) | (ret_pack[1] << 8) | (ret_pack[2] << 16) | (ret_pack[3] << 24));
		}
		else
		{
			time = -1;
			break;
		}
	}while(0);

	return time;
 }



/**
 * @brief	保存当前配置到内部Flash
 * @param[in]	devAddr      设备地址
 * @note
 * @see
 * @code
 *
 * @retval	成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_ProfileSaveToCurrent(uint8_t devAddr)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xfe;
		args[indx++] = 0x3f;
		ret = Cmd_CreatePack(packbuf, CMD_SAVE_PROFILE, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_SAVE_PROFILE, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	删除用户设置表
 * @param[in]	devAddr     设备地址
 * @note
 * @see
 * @code
 *
 * @retval	成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_ProfileClearCurrent(uint8_t devAddr)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xfe;
		args[indx++] = 0x3f;
		ret = Cmd_CreatePack(packbuf, CMD_CLEAR_PROFILE, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_CLEAR_PROFILE, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	恢复出厂设置
 * @param[in]	devAddr     设备地址
 * @note
 * @see
 * @code
 *
 * @retval	返回恢复出厂设置的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_ProfileRestoreFactory(uint8_t devAddr)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xf0;
		args[indx++] = 0x1f;
		ret = Cmd_CreatePack(packbuf, CMD_RESTORE_FACTORY, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_RESTORE_FACTORY, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	选择ROI组
 * @param[in]	devAddr       设备地址
 * @param[in]	group_id     ROI组选择输入
 * @note
 * @see
 * @code
 *
 * @retval	返回选择ROI组的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SelectROIGroup(uint8_t devAddr, uint8_t group_id)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa9;
		args[indx++] = group_id;
		ret = Cmd_CreatePack(packbuf, CMD_ROI, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_ROI, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}

/**
 * @brief	获取当前ROI组ID
 * @param[in]	devAddr     设备地址
 * @note
 * @see
 * @code
 *
 * @retval	返回当前ROI组ID
 */
int8_t HPS3D_GetROIGroupID(uint8_t devAddr)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;
	uint8_t group_id = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xaa;/*设置警报类型*/
		ret = Cmd_CreatePack(packbuf, CMD_ROI, args,indx);
		if( ret != RET_OK )
		{
			group_id = 0xff;
			break;
		}

		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			group_id = 0xff;
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_ROI, ret_pack);
		if( retback_len > 0 )
		{
			group_id = ret_pack[0];
		}
		else
		{
			group_id = 0xff;
			break;
		}
	}while(0);
	return group_id;
}


/**
 * @brief	设置ROI的警报类型
 * @param[in]	devAddr       设备地址
 * @param[in]	group_id     ROI组选择输入
 * @param[in]	threshold_id 阈值选择输入
 * @param[in]	type	     警报类型选择输入
 * @note
 * @see
 * @code
 *
 * @retval	返回设置ROI的警报类型的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetROIAlarmType(uint8_t devAddr, uint8_t roi_id, uint8_t threshold_id, ROIAlarmTypeDef type)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa8;/*设置警报类型*/
		args[indx++] = roi_id;
		args[indx++] = threshold_id;
		args[indx++] = (uint8_t)type;

		ret = Cmd_CreatePack(packbuf, CMD_ROI, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_ROI, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	设定数据包类型
 * @param[in]	devAddr       设备地址
 * @param[in]	type	     数据包类型选择输入
 * @note
 * @see
 * @code
 *
 * @retval	返回设定数据包类型的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetPacketType(uint8_t devAddr, PacketTypeDef type)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x01;/*设置数据包的类型*/
		args[indx++] = (uint8_t)type;
		ret = Cmd_CreatePack(packbuf, CMD_PACKET_TYPE, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_PACKET_TYPE, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


 /**
 * @brief	获取数据包类型
 * @param[in]	devAddr       设备地址
 * @note
 * @see
 * @code
 *
 * @retval	返回数据包类型
 */
 PacketTypeDef HPS3D_GetPacketType(uint8_t devAddr)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;
	PacketTypeDef type = PACKET_FULL;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x2;

		ret = Cmd_CreatePack(packbuf, CMD_PACKET_TYPE, args, indx);
		if( ret != RET_OK )
		{
			type = PACKET_UNKNOWN;
			break;
		}

		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			type = PACKET_UNKNOWN;
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_PACKET_TYPE, ret_pack);
		if( retback_len > 0 )
		{
			type = (PacketTypeDef)ret_pack[0];
		}
		else
		{
			type = PACKET_UNKNOWN;
			break;
		}
	}while(0);

	return type;
}


 /**
 * @brief	设置ROI的参考值类型
 * @param[in]	devAddr       设备地址
 * @param[in]	roi_id       ROI组ID选择输入
 * @param[in]	threshold_id 阈值选择输入
 * @param[in]	type	     参考值类型选择输入
 * @note
 * @see
 * @code
 *
 * @retval	返回设置ROI的参考值类型的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetROIReferenceType(uint8_t devAddr, uint8_t roi_id, uint8_t threshold_id, ROIReferenceTypeDef type)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa7;/*设置参考类型*/
		args[indx++] = roi_id;
		args[indx++] = threshold_id;
		args[indx++] = (uint8_t)type;
		ret = Cmd_CreatePack(packbuf, CMD_ROI, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_ROI, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}

/**
 * @brief	设定ROI区域
 * @param[in]	devAddr          设备地址
 * @param[in]	roi_id          ROI组ID选择输入
 * @param[in]	left_top_x		左上角x坐标
 * @param[in]	left_top_y		左上角y坐标
 * @param[in]	right_bottom_x  右下角x坐标
 * @param[in]   right_bottom_y  右下角y坐标
 * @note
 * @see
 * @code
 *
 * @retval	返回设定ROI区域的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetROIRegion(uint8_t devAddr, uint8_t roi_id, uint16_t left_top_x, uint16_t left_top_y, uint16_t right_bottom_x, uint16_t right_bottom_y)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa1;/*set roi settings*/
		args[indx++] = roi_id;
		args[indx++] = (uint8_t)(left_top_x >> 0);
		args[indx++] = (uint8_t)(left_top_x >> 8);
		args[indx++] = (uint8_t)(left_top_y >> 0);
		args[indx++] = (uint8_t)(left_top_y >> 8);
		args[indx++] = (uint8_t)(right_bottom_x >> 0);
		args[indx++] = (uint8_t)(right_bottom_x >> 8);
		args[indx++] = (uint8_t)(right_bottom_y >> 0);
		args[indx++] = (uint8_t)(right_bottom_y >> 8);
		ret = Cmd_CreatePack(packbuf, CMD_ROI, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_ROI, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}

/**
 * @brief	设置ROI使能
 * @param[in]	devAddr      设备地址
 * @param[in]	id          ROI组ID选择输入
 * @param[in]	en     		使能
 * @note
 * @see
 * @code
 *
 * @retval	返回设置ROI使能的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetROIEnable(uint8_t devAddr, uint32_t id, bool en)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa2;/*set roi en*/
		args[indx++] = (uint8_t)id;
		args[indx++] = (uint8_t)((en) ? 1 : 0);
		ret = Cmd_CreatePack(packbuf, CMD_ROI, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_ROI, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	设置ROI阈值使能
 * @param[in]	devAddr       设备地址
 * @param[in]	id           ROI组ID选择输入
 * @param[in]	threshold_id 阈值选择输入
 * @param[in]	en     		 使能
 * @note
 * @see
 * @code
 *
 * @retval	返回设置ROI阈值使能的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetROIThresholdEnable(uint8_t devAddr, uint32_t roi_id, uint32_t threshold_id, bool en)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa5;
		args[indx++] = (uint8_t)roi_id;
		args[indx++] = (uint8_t)threshold_id;
		args[indx++] = (uint8_t)((en) ? 1 : 0);
		ret = Cmd_CreatePack(packbuf, CMD_ROI, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_ROI, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}

/**
 * @brief	设置ROI阈值配置
 * @param[in]	devAddr       		设备地址
 * @param[in]	roi_id       		ROI组ID选择输入
 * @param[in]	threshold_id 		阈值id选择输入
 * @param[in]	threshold			阈值
 * @param[in]	hysteresis  		迟滞（死区）大小
 * @param[in]	positive	 		比较器极性，true:正向比较, false：反向比较
 * @param[in]   pix_num_threshold   超过阈值的像素点数
 * @note
 * @see
 * @code
 *
 * @retval	返回设置ROI阈值配置的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetROIThresholdConf(uint8_t devAddr, uint32_t roi_id, uint32_t threshold_id, uint32_t threshold, uint32_t hysteresis, bool positive, uint16_t pix_num_threshold)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa4;
		args[indx++] = (uint8_t)roi_id;
		args[indx++] = (uint8_t)threshold_id;
		args[indx++] = (uint8_t)(threshold >> 0);
		args[indx++] = (uint8_t)(threshold >> 8);
		args[indx++] = (uint8_t)(threshold >> 16);
		args[indx++] = (uint8_t)(threshold >> 24);
		args[indx++] = (uint8_t)(hysteresis >> 0);
		args[indx++] = (uint8_t)(hysteresis >> 8);
		args[indx++] = (uint8_t)(hysteresis >> 16);
		args[indx++] = (uint8_t)(hysteresis >> 24);
		args[indx++] = (uint8_t)(positive ? 1 : 0);
		args[indx++] = (uint8_t)(pix_num_threshold >> 0);
		args[indx++] = (uint8_t)(pix_num_threshold >> 8);
		ret = Cmd_CreatePack(packbuf, CMD_ROI, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_ROI, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}

/**
 * @brief	获取当前设备支持的ROI数量和阈值数量
 * @param[in]	devAddr           设备地址
 * @param[out]	roi_number       ROI组ID的数量
 * @param[out]	threshold_number 阈值的数量
 * @note
 * @see
 * @code
 *
 * @retval	返回获取当前设备支持的ROI数量和阈值数量的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_GetNumberOfROI(uint8_t devAddr, uint8_t *roi_number, uint8_t *threshold_number)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		*roi_number = 0;
		*threshold_number = 0;
		args[indx++] = devAddr;
		args[indx++] = 0xa6;
		ret = Cmd_CreatePack(packbuf, CMD_ROI, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_ROI, ret_pack);
		if( retback_len > 0 )
		{
			*roi_number = ret_pack[0];
			*threshold_number = ret_pack[1];
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}

/**
 * @brief	获取指定的ROI配置
 * @param[in]	devAddr      设备地址
 * @param[in]	id          ROI编号，从0开始, 数量可通过GetNumberOfROI()获取
 * @param[out]	conf		获取指定的ROI配置的结构体指针
 * @note
 * @see
 * @code
 *
 * @retval	返回获得指定的ROI配置的结果，成功返回 RET_OK
 */

 RET_StatusTypeDef HPS3D_GetROIConfById(uint8_t devAddr, uint32_t id, ROIConfTypeDef *conf)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	/*用于记录返回解析后的数据包的位置*/
	uint8_t idx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa3;/*get roi conf by id*/
		args[indx++] = (uint8_t)id;
		ret = Cmd_CreatePack(packbuf, CMD_ROI, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_ROI, ret_pack);
		if( retback_len > 0 )
		{
			conf->roi_id = ret_pack[idx++];
			conf->enable = (ret_pack[idx++] > 0) ? true : false;

			conf->left_top_x = (uint16_t)(ret_pack[idx++] << 0);
			conf->left_top_x += (uint16_t)(ret_pack[idx++] << 8);
			conf->left_top_y = (uint16_t)(ret_pack[idx++] << 0);
			conf->left_top_y += (uint16_t)(ret_pack[idx++] << 8);
			conf->right_bottom_x = (uint16_t)(ret_pack[idx++] << 0);
			conf->right_bottom_x += (uint16_t)(ret_pack[idx++] << 8);
			conf->right_bottom_y = (uint16_t)(ret_pack[idx++] << 0);
			conf->right_bottom_y += (uint16_t)(ret_pack[idx++] << 8);
			conf->hysteresis_conf[0].roi_id = ret_pack[idx++];
			conf->hysteresis_conf[0].enable = (ret_pack[idx++] > 0) ? true : false;

			conf->hysteresis_conf[0].threshold_value = (uint32_t)(ret_pack[idx++] << 0);
			conf->hysteresis_conf[0].threshold_value += (uint32_t)(ret_pack[idx++] << 8);
			conf->hysteresis_conf[0].threshold_value += (uint32_t)(ret_pack[idx++] << 16);
			conf->hysteresis_conf[0].threshold_value += (uint32_t)(ret_pack[idx++] << 24);

			conf->hysteresis_conf[0].hysteresis = (uint32_t)(ret_pack[idx++] << 0);
			conf->hysteresis_conf[0].hysteresis += (uint32_t)(ret_pack[idx++] << 8);
			conf->hysteresis_conf[0].hysteresis += (uint32_t)(ret_pack[idx++] << 16);
			conf->hysteresis_conf[0].hysteresis += (uint32_t)(ret_pack[idx++] << 24);

			conf->hysteresis_conf[0].positive = (ret_pack[idx++] > 0) ? true : false;
			conf->ref_type[0] = (ROIReferenceTypeDef)(ret_pack[idx++]);
			conf->alarm_type[0] = (ROIAlarmTypeDef)(ret_pack[idx++]);
			conf->pixel_number_threshold[0] = (uint16_t)(ret_pack[idx++] << 0);
			conf->pixel_number_threshold[0] += (uint16_t)(ret_pack[idx++] << 8);

			conf->hysteresis_conf[1].roi_id = ret_pack[idx++];
			conf->hysteresis_conf[1].enable = (ret_pack[idx++] > 0) ? true : false;

			conf->hysteresis_conf[1].threshold_value = (uint32_t)(ret_pack[idx++] << 0);
			conf->hysteresis_conf[1].threshold_value += (uint32_t)(ret_pack[idx++] << 8);
			conf->hysteresis_conf[1].threshold_value += (uint32_t)(ret_pack[idx++] << 16);
			conf->hysteresis_conf[1].threshold_value += (uint32_t)(ret_pack[idx++] << 24);

			conf->hysteresis_conf[1].hysteresis = (uint32_t)(ret_pack[idx++] << 0);
			conf->hysteresis_conf[1].hysteresis += (uint32_t)(ret_pack[idx++] << 8);
			conf->hysteresis_conf[1].hysteresis += (uint32_t)(ret_pack[idx++] << 16);
			conf->hysteresis_conf[1].hysteresis += (uint32_t)(ret_pack[idx++] << 24);

			conf->hysteresis_conf[1].positive = (ret_pack[idx++] > 0) ? true : false;
			conf->ref_type[1] = (ROIReferenceTypeDef)(ret_pack[idx++]);
			conf->alarm_type[1] = (ROIAlarmTypeDef)(ret_pack[idx++]);
			conf->pixel_number_threshold[1] = (uint16_t)(ret_pack[idx++] << 0);
			conf->pixel_number_threshold[1] += (uint16_t)(ret_pack[idx++] << 8);

			conf->hysteresis_conf[2].roi_id = ret_pack[idx++];
			conf->hysteresis_conf[2].enable = (ret_pack[idx++] > 0) ? true : false;

			conf->hysteresis_conf[2].threshold_value = (uint32_t)(ret_pack[idx++] << 0);
			conf->hysteresis_conf[2].threshold_value += (uint32_t)(ret_pack[idx++] << 8);
			conf->hysteresis_conf[2].threshold_value += (uint32_t)(ret_pack[idx++] << 16);
			conf->hysteresis_conf[2].threshold_value += (uint32_t)(ret_pack[idx++] << 24);

			conf->hysteresis_conf[2].hysteresis = (uint32_t)(ret_pack[idx++] << 0);
			conf->hysteresis_conf[2].hysteresis += (uint32_t)(ret_pack[idx++] << 8);
			conf->hysteresis_conf[2].hysteresis += (uint32_t)(ret_pack[idx++] << 16);

			conf->hysteresis_conf[2].hysteresis += (uint32_t)(ret_pack[idx++] << 24);
			conf->hysteresis_conf[2].positive = (ret_pack[idx++] > 0) ? true : false;
			conf->ref_type[2] = (ROIReferenceTypeDef)(ret_pack[idx++]);
			conf->alarm_type[2] = (ROIAlarmTypeDef)(ret_pack[idx++]);
			conf->pixel_number_threshold[2] = (uint16_t)(ret_pack[idx++] << 0);
			conf->pixel_number_threshold[2] += (uint16_t)(ret_pack[idx++] << 8);
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}

/**
 * @brief	设置HDR模式
 * @param[in]	devAddr        设备地址
 * @param[in]	conf		  HRD配置
 * @note
 * @see
 * @code
 *
 * @retval	返回设置HDR模式的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetHDRMode(uint8_t devAddr, HDRConfTypeDef conf)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa1;/*set*/
		args[indx++] = (uint8_t)conf.hdr_mode;
		ret = Cmd_CreatePack(packbuf, CMD_HDR_CONFIG, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_HDR_CONFIG, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}

/**
 * @brief	设置AutoHDR
 * @param[in]	devAddr        设备地址
 * @param[in]	conf		  HRD配置
 * @note
 * @see
 * @code
 *
 * @retval	返回设置AutoHDR的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetAutoHDRConfig(uint8_t devAddr, HDRConfTypeDef conf)
{
	uint8_t args[50];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa2;/*set*/
		args[indx++] = conf.hdr_divisor;
		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_overexposed * 1000) >> 0);
		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_overexposed * 1000) >> 8);
		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_overexposed * 1000) >> 16);
		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_overexposed * 1000) >> 24);

		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_overexposed_serious * 1000) >> 0);
		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_overexposed_serious * 1000) >> 8);
		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_overexposed_serious * 1000) >> 16);
		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_overexposed_serious * 1000) >> 24);

		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_weak * 1000) >> 0);
		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_weak * 1000) >> 8);
		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_weak * 1000) >> 16);
		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_weak * 1000) >> 24);

		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_weak_serious * 1000) >> 0);
		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_weak_serious * 1000) >> 8);
		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_weak_serious * 1000) >> 16);
		args[indx++] = (uint8_t)((int32_t)(conf.qualtity_weak_serious * 1000) >> 24);

		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_overexposed_ratio * 1000) >> 0);
		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_overexposed_ratio * 1000) >> 8);
		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_overexposed_ratio * 1000) >> 16);
		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_overexposed_ratio * 1000) >> 24);

		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_overexposed_ratio2 * 1000) >> 0);
		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_overexposed_ratio2 * 1000) >> 8);
		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_overexposed_ratio2 * 1000) >> 16);
		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_overexposed_ratio2 * 1000) >> 24);

		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_weak_ratio * 1000) >> 0);
		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_weak_ratio * 1000) >> 8);
		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_weak_ratio * 1000) >> 16);
		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_weak_ratio * 1000) >> 24);

		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_weak_ratio2 * 1000) >> 0);
		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_weak_ratio2 * 1000) >> 8);
		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_weak_ratio2 * 1000) >> 16);
		args[indx++] = (uint8_t)((int32_t)(conf.int_adjust_weak_ratio2 * 1000) >> 24);

		args[indx++] = (uint8_t)conf.super_hdr_frame_number;

		args[indx++] = (uint8_t)((conf.super_hdr_max_integration) >> 0);
		args[indx++] = (uint8_t)((conf.super_hdr_max_integration) >> 8);
		args[indx++] = (uint8_t)((conf.super_hdr_max_integration) >> 16);
		args[indx++] = (uint8_t)((conf.super_hdr_max_integration) >> 24);


		ret = Cmd_CreatePack(packbuf, CMD_HDR_CONFIG, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_HDR_CONFIG, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	设置SuperHDR
 * @param[in]	devAddr        设备地址
 * @param[in]	conf		  HRD配置
 * @note
 * @see
 * @code
 *
 * @retval	返回设置AutoHDR的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetSuperHDRConfig(uint8_t devAddr, HDRConfTypeDef conf)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa3;/*set*/
		args[indx++] = (uint8_t)conf.super_hdr_frame_number;
		args[indx++] = (uint8_t)((conf.super_hdr_max_integration) >> 0);
		args[indx++] = (uint8_t)((conf.super_hdr_max_integration) >> 8);
		args[indx++] = (uint8_t)((conf.super_hdr_max_integration) >> 16);
		args[indx++] = (uint8_t)((conf.super_hdr_max_integration) >> 24);

		ret = Cmd_CreatePack(packbuf, CMD_HDR_CONFIG, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_HDR_CONFIG, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	设置简单HDR
 * @param[in]	devAddr        设备地址
 * @param[in]	conf		  HRD配置
 * @note
 * @see
 * @code
 *
 * @retval	返回设置简单HDR的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetSimpleHDRConfig(uint8_t devAddr, HDRConfTypeDef conf)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa4;/*set*/
		args[indx++] = (uint8_t)((conf.simple_hdr_max_integration) >> 0);
		args[indx++] = (uint8_t)((conf.simple_hdr_max_integration) >> 8);
		args[indx++] = (uint8_t)((conf.simple_hdr_max_integration) >> 16);
		args[indx++] = (uint8_t)((conf.simple_hdr_max_integration) >> 24);
		args[indx++] = (uint8_t)((conf.simple_hdr_min_integration) >> 0);
		args[indx++] = (uint8_t)((conf.simple_hdr_min_integration) >> 8);
		args[indx++] = (uint8_t)((conf.simple_hdr_min_integration) >> 16);
		args[indx++] = (uint8_t)((conf.simple_hdr_min_integration) >> 24);

		ret = Cmd_CreatePack(packbuf, CMD_HDR_CONFIG, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_HDR_CONFIG, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	获取AutoHDR设置
 * @param[in]	devAddr        设备地址
 * @param[out]	conf		  获取AutoHDR设置的结构体指针
 * @note
 * @see
 * @code
 *
 * @retval	返回获取AutoHDR设置的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_GetHDRConfig(uint8_t devAddr, HDRConfTypeDef *conf)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	/*用于记录返回解析后的数据包的位置*/
	uint8_t idx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x02;/*get*/
		ret = Cmd_CreatePack(packbuf, CMD_HDR_CONFIG, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf,CMD_HDR_CONFIG,ret_pack);
		if( retback_len > 0 )
		{
			conf->hdr_divisor = ret_pack[idx++];
			conf->hdr_mode = (HDRModeTypeDef)ret_pack[idx++];

			conf->qualtity_overexposed = ((ret_pack[idx + 0] << 0) | (ret_pack[idx + 1] << 8) | (ret_pack[idx + 2] << 16) | ret_pack[idx + 3] << 24) / 1000.0f;
			idx += 4;

			conf->qualtity_overexposed_serious = ((ret_pack[idx + 0] << 0) | (ret_pack[idx + 1] << 8) | (ret_pack[idx + 2] << 16) | ret_pack[idx + 3] << 24) / 1000.0f;
			idx += 4;

			conf->qualtity_weak = ((ret_pack[idx + 0] << 0) | (ret_pack[idx + 1] << 8) | (ret_pack[idx + 2] << 16) | ret_pack[idx + 3] << 24) / 1000.0f;
			idx += 4;

			conf->qualtity_weak_serious = ((ret_pack[idx + 0] << 0) | (ret_pack[idx + 1] << 8) | (ret_pack[idx + 2] << 16) | ret_pack[idx + 3] << 24) / 1000.0f;
			idx += 4;

			conf->int_adjust_overexposed_ratio = ((ret_pack[idx + 0] << 0) | (ret_pack[idx + 1] << 8) | (ret_pack[idx + 2] << 16) | ret_pack[idx + 3] << 24) / 1000.0f;
			idx += 4;

			conf->int_adjust_overexposed_ratio2 = ((ret_pack[idx + 0] << 0) | (ret_pack[idx + 1] << 8) | (ret_pack[idx + 2] << 16) | ret_pack[idx + 3] << 24) / 1000.0f;
			idx += 4;

			conf->int_adjust_weak_ratio = ((ret_pack[idx + 0] << 0) | (ret_pack[idx + 1] << 8) | (ret_pack[idx + 2] << 16) | ret_pack[idx + 3] << 24) / 1000.0f;
			idx += 4;

			conf->int_adjust_weak_ratio2 = ((ret_pack[idx + 0] << 0) | (ret_pack[idx + 1] << 8) | (ret_pack[idx + 2] << 16) | ret_pack[idx + 3] << 24) / 1000.0f;
			idx += 4;

			conf->super_hdr_frame_number = ret_pack[idx];
			idx += 1;

			conf->super_hdr_max_integration = (uint32_t)((ret_pack[idx + 0] << 0) | (ret_pack[idx + 1] << 8) | (ret_pack[idx + 2] << 16) | ret_pack[idx + 3] << 24);
			idx += 4;

			conf->simple_hdr_max_integration = (uint32_t)((ret_pack[idx + 0] << 0) | (ret_pack[idx + 1] << 8) | (ret_pack[idx + 2] << 16) | ret_pack[idx + 3] << 24);
			idx += 4;

			conf->simple_hdr_min_integration = (uint32_t)((ret_pack[idx + 0] << 0) | (ret_pack[idx + 1] << 8) | (ret_pack[idx + 2] << 16) | ret_pack[idx + 3] << 24);
			idx += 4;
		}
		else
		{
			ret = RET_ERROR;
			break;
		}

	}while(0);

	return ret;
}


/**
 * @brief	设置指定的GPIO输出端口的配置
 * @param[in]	devAddr        设备地址
 * @param[in]	gpio		  gpio端口号选择
 * @param[in]	func      	  gpio功能选择
 * @param[in]	polarity	  gpio极性选择
 * @note
 * @see
 * @code
 *
 * @retval	返回设置指定的GPIO输出端口的配置的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetGPIOOut(uint8_t devAddr, GPIOTypeDef gpio, GPOutFunctionTypeDef func, GPIOPolarityTypeDef polarity)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x01;
		args[indx++] = (uint8_t)gpio;
		args[indx++] = (uint8_t)func;
		args[indx++] = (uint8_t)polarity;

		ret = Cmd_CreatePack(packbuf, CMD_GPIO_OUT, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_GPIO_OUT, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}

/**
 * @brief	获取指定GPIO输出端口的配置
 * @param[in]	devAddr        设备地址
 * @param[in]	gpio		  gpio端口号选择
 * @param[out]	gpio_conf     获取gpio配置的结构体指针
 * @note
 * @see
 * @code
 *
 * @retval	返回获取指定GPIO输出端口的配置的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_GetGPIOOutConf(uint8_t devAddr, GPIOTypeDef gpio, GPIOOutConfTypeDef *gpio_conf)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x02;
		args[indx++] = (uint8_t)gpio;

		ret = Cmd_CreatePack(packbuf, CMD_GPIO_OUT, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_GPIO_OUT, ret_pack);
		if(retback_len > 0 )
		{
			gpio_conf->gpio = gpio;
			gpio_conf->function = (GPOutFunctionTypeDef)ret_pack[0];
			gpio_conf->polarity = (GPIOPolarityTypeDef)ret_pack[1];
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}




/**
 * @brief	设定光学补偿使能
 * @param[in]	devAddr        设备地址
 * @param[in]	en			  使能信号
 * @note
 * @see
 * @code
 *
 * @retval	返回设定光学参数使能的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetOpticalEnable(uint8_t devAddr, bool en)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x01;
		args[indx++] = (uint8_t)(en ? 0x10 : 0x00);

		ret = Cmd_CreatePack(packbuf, CMD_OPTICAL_PARAM, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_OPTICAL_PARAM, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] > 0)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	获取光学参数
 * @param[in]	devAddr        设备地址
 * @param[in]	conf		  获取光学参数的结构体指针
 * @note
 * @see
 * @code
 *
 * @retval	返回设定光学参数的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_GetOpticalParamConf(uint8_t devAddr, OpticalParamConfTypeDef *conf)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	/*用于记录返回解析后的数据包的位置*/
	uint8_t idx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x03;

		ret = Cmd_CreatePack(packbuf, CMD_OPTICAL_PARAM, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_OPTICAL_PARAM, ret_pack);
		if( retback_len > 0 )
		{
			conf->enable = (ret_pack[idx++] > 0) ? true : false;
			conf->viewing_angle_horiz = ret_pack[idx++];
			conf->viewing_angle_vertical = ret_pack[idx++];
			conf->illum_angle_horiz = ret_pack[idx++];
			conf->illum_angle_vertical = ret_pack[idx++];
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}



 /**
 * @brief	设置距离补偿
 * @param[in]	devAddr        设备地址
 * @param[in]	offset		  补偿距离
 * @note
 * @see
 * @code
 *
 * @retval	返回设置距离补偿的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetDistanceOffset(uint8_t devAddr, int16_t offset)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x01;
		args[indx++] = (uint8_t)(offset >> 0);
		args[indx++] = (uint8_t)(offset >> 8);

		ret = Cmd_CreatePack(packbuf, CMD_DISTANCE_OFFSET, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_DISTANCE_OFFSET, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] > 0)
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}

 /**
 * @brief	获得距离补偿
 * @param[in]	devAddr        设备地址
 * @note
 * @see
 * @code
 *
 * @retval	返回获得距离补偿的值
 */
 int16_t HPS3D_GetDistanceOffset(uint8_t devAddr)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;
	int16_t offset = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x02;

		Cmd_CreatePack(packbuf, CMD_DISTANCE_OFFSET, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_DISTANCE_OFFSET, ret_pack);
		if( retback_len > 0 )
		{
			offset = (int16_t)(ret_pack[1] * 256 + ret_pack[0]);
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return offset;
}



/**
 * @brief	设置指定的GPIO输入端口的配置
 * @param[in]	devAddr        设备地址
 * @param[in]	gpio		  		gpio端口号选择
 * @param[in]	func      	  gpio功能选择
 * @param[in]	polarity	  	gpio极性选择
 * @note
 * @see
 * @code
 *
 * @retval	返回设置指定的GPIO输入端口的配置的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetGPIOIn(uint8_t devAddr, GPIOTypeDef gpio, GPInFunctionTypeDef func, GPIOPolarityTypeDef polarity)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x01;
		args[indx++] = (uint8_t)gpio;
		args[indx++] = (uint8_t)func;
		args[indx++] = (uint8_t)polarity;

		ret = Cmd_CreatePack(packbuf, CMD_GPIO_IN, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_GPIO_IN, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1 )
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	获取指定GPIO输入端口的配置
 * @param[in]	devAddr        设备地址
 * @param[in]	gpio		  gpio端口号选择
 * @param[out]	gpio_conf     获取gpio配置的结构体指针
 * @note
 * @see
 * @code
 *
 * @retval	返回获取指定GPIO输入端口的配置的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_GetGPIOInConf(uint8_t devAddr, GPIOTypeDef gpio, GPIOInConfTypeDef *gpio_conf)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x02;
		args[indx++] = (uint8_t)gpio;

		ret = Cmd_CreatePack(packbuf, CMD_GPIO_IN, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_GPIO_IN, ret_pack);
		if( retback_len > 0 )
		{
			gpio_conf->gpio = gpio;
			gpio_conf->function = (GPInFunctionTypeDef)ret_pack[0];
			gpio_conf->polarity = (GPIOPolarityTypeDef)ret_pack[1];
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}






/**
 * @brief	测试GPOUT的输出信号
 * @param[in]	devAddr        设备地址
 * @param[in]	value
 * @note
 * @see
 * @code
 *
 * @retval	返回测试GPOUT的输出信号的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetGPOUT1_Val(uint8_t devAddr, uint8_t value)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0x03;
		args[indx++] = value;
		ret = Cmd_CreatePack(packbuf, CMD_GPIO_OUT, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_GPIO_OUT, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] > 0 )
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	设置距离滤波器类型
 * @param[in]	devAddr        设备地址
 * @param[in]	type		  滤波器类型
 * @note
 * @see
 * @code
 *
 * @retval	返回设置滤波器类型的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetDistanceFilterType(uint8_t devAddr, DistanceFilterTypeDef type)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa1;
		args[indx++] = (uint8_t)type;

		ret = Cmd_CreatePack(packbuf, CMD_DISTANCE_FILTER, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_DISTANCE_FILTER, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1 )
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


/**
 * @brief	设置Simple Kalman滤波器
 * @param[in]	devAddr        设备地址
 * @param[in]	conf		  Simple Kalman的配置
 * @note
 * @see
 * @code
 *
 * @retval	返回设置Simple Kalman的结果，成功返回 RET_OK
 */
 RET_StatusTypeDef HPS3D_SetSimpleKalman(uint8_t devAddr, DistanceFilterConfTypeDef conf)
{
	uint8_t args[20];
	/*用于记录参数的个数*/
	uint8_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	/*packbuf[256]：命令包；retbuf[256]：命令返回包；ret_pack[256]：解析后的数据包；*/
	uint8_t packbuf[256] = {0}, retbuf[256] = {0}, ret_pack[256] = {0};
	uint32_t retback_len = 0;

	do
	{
		args[indx++] = devAddr;
		args[indx++] = 0xa2;/*set*/
		args[indx++] = (uint8_t)((uint32_t)(conf.kalman_K * 1000) >> 0);
		args[indx++] = (uint8_t)((uint32_t)(conf.kalman_K * 1000) >> 8);
		args[indx++] = (uint8_t)((uint32_t)(conf.kalman_K * 1000) >> 16);
		args[indx++] = (uint8_t)((uint32_t)(conf.kalman_K * 1000) >> 24);
		args[indx++] = (uint8_t)((conf.num_check) >> 0);
		args[indx++] = (uint8_t)((conf.num_check) >> 8);
		args[indx++] = (uint8_t)((conf.num_check) >> 16);
		args[indx++] = (uint8_t)((conf.num_check) >> 24);
		args[indx++] = (uint8_t)((uint32_t)(conf.kalman_threshold) >> 0);
		args[indx++] = (uint8_t)((uint32_t)(conf.kalman_threshold) >> 8);
		args[indx++] = (uint8_t)((uint32_t)(conf.kalman_threshold) >> 16);
		args[indx++] = (uint8_t)((uint32_t)(conf.kalman_threshold) >> 24);

		ret = Cmd_CreatePack(packbuf, CMD_DISTANCE_FILTER, args, indx);
		if( ret != RET_OK )
		{
			break;
		}
		/*此处调用读写函数,实现命令发送与返回包读取，数据包的长度=2+1+1+参数的长度+2*/
		ret = HAL_SimpleCommunication(packbuf, indx + 6, retbuf, 500);
		if( ret != RET_OK )
		{
			break;
		}

		retback_len = Cmd_UnPack(retbuf, CMD_DISTANCE_FILTER, ret_pack);
		if( retback_len > 0 )
		{
			if (ret_pack[0] == 1 )
			{
				break;
			}
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}

/**
 * @brief	数据包CRC16校验
 * @param[in]	buf[]    数据包
 * @param[in]	buf_len  buf[]的长度
 * @note
 * @see
 * @code
 *
 * @retval	返回数据包CRC16校验结果
 */
RET_StatusTypeDef CRC_VerifyPacket(uint8_t *buf,uint32_t buf_len)
{
	RET_StatusTypeDef ret = RET_OK;
	uint32_t crc16_pack = 0;
	uint32_t crc16 = 0;
	do
	{
		/*验证报头报尾及CRC校验值*/
		if (buf[0] == PACKET_HEAD1 && buf[1] == PACKET_HEAD2
			   && buf[buf_len - 2] == PACKET_TAIL1 && buf[buf_len - 1] == PACKET_TAIL2)
		{
		   crc16_pack = crc16_cal(buf + 4, buf_len - 8);
		   crc16 = (uint16_t)((buf[buf_len - 3]) << 8 | (buf[buf_len - 4]) << 0);
		   if (crc16 != crc16_pack)
		   {
			   	 ret = RET_ERROR;
			   	 break;
		   }
		}
		else
		{
			ret = RET_ERROR;
			break;
		}
	}while(0);

	return ret;
}


