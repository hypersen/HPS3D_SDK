/**********************************************************************
* COPYRIGHT NOTICE - HYPERSEN TECHNOLOGY
*
* Copyright (c) 2018, Hypersen Technology, Inc.
*
* All rights reserved.
*
*======================================================================
* \file hal.h
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

#include <stdint.h>

#ifndef HPS3DTOFSDKLITE_INC_HAL_H_
#define HPS3DTOFSDKLITE_INC_HAL_H_

void Uart_Read(uint8_t *dest_buff, uint16_t length, uint32_t timeout_ms);
void Uart_Write(uint8_t *from_buff, uint16_t length, uint32_t timeout_ms);
void Delay_Ms(uint16_t ms);

#endif

