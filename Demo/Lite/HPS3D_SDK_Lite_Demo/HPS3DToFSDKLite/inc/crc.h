/**********************************************************************
* COPYRIGHT NOTICE - HYPERSEN TECHNOLOGY
*
* Copyright (c) 2018, Hypersen Technology, Inc.
*
* All rights reserved.
*
*======================================================================
* \file crc.h
* \brief TODO
* \author Joker
* \email Joker_Wu@hypersen.com
* \version 1.0.0
* \date 2018年6月7日 下午8:26:06
* \license private & classified
*---------------------------------------------------------------------
* Remark: This project is still under construction.
*======================================================================
* Change History:
*---------------------------------------------------------------------
* <Date>			| <Version>	| <Author>			| <Description>
*---------------------------------------------------------------------
* 2018年6月7日			| V1.0.0	| Joker				| Create file
*======================================================================
* Detailed Notes:
*---------------------------------------------------------------------
* <Version>		| <Description>
*---------------------------------------------------------------------
* V1.0.0		| TODO
*---------------------------------------------------------------------

**********************************************************************/

#ifndef HPS3DTOFSDKLITE_INC_CRC_H_
#define HPS3DTOFSDKLITE_INC_CRC_H_

#include <stdint.h>

uint32_t crc32_cal(uint8_t *data, uint32_t len);
uint16_t crc16_cal(uint8_t* ptr, uint16_t len);

#endif /* INC_CRC_H_ */

