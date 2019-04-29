/**********************************************************************
* COPYRIGHT NOTICE - HYPERSEN TECHNOLOGY
*
* Copyright (c) 2018, Hypersen Technology, Inc.
*
* All rights reserved.
*
*======================================================================
* \file hal.c
* \brief TODO
* \author Joker
* \email Joker_Wu@hypersen.com
* \version 1.0.0
* \date 2018年12月2日 下午3:07:24
* \license private & classified
*---------------------------------------------------------------------
* Remark: This project is still under construction.
*======================================================================
* Change History:
*---------------------------------------------------------------------
* <Date>			| <Version>	| <Author>			| <Description>
*---------------------------------------------------------------------
* 2018年12月2日			| V1.0.0	| Joker				| Create file
*======================================================================
* Detailed Notes:
*---------------------------------------------------------------------
* <Version>		| <Description>
*---------------------------------------------------------------------
* V1.0.0		| TODO
*---------------------------------------------------------------------

**********************************************************************/

#include "HPS3DToFSDKLite/inc/hal.h"
#include "usart.h"

void Uart_Read(uint8_t *dest_buff, uint16_t length, uint32_t timeout_ms)
{
	HAL_UART_Receive(&huart1, dest_buff, length, timeout_ms);
}

void Uart_Write(uint8_t *from_buff, uint16_t length, uint32_t timeout_ms)
{
	HAL_UART_Transmit(&huart1, from_buff, length, timeout_ms);
}

void Delay_Ms(uint16_t ms)
{
	HAL_Delay(ms);
}
