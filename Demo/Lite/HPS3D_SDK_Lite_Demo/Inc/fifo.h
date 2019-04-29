/**********************************************************************
* COPYRIGHT NOTICE - HYPERSEN TECHNOLOGY
*
* Copyright (c) 2018, Hypersen Technology, Inc.
*
* All rights reserved.
*
*======================================================================
* \file fifo.h
* \brief TODO	无锁FIFO
* \author Joker
* \email Joker_Wu@hypersen.com
* \version 1.0.0
* \date 2018年7月24日 下午12:19:06
* \license private & classified
*---------------------------------------------------------------------
* Remark: This project is still under construction.
*======================================================================
* Change History:
*---------------------------------------------------------------------
* <Date>			| <Version>	| <Author>			| <Description>
*---------------------------------------------------------------------
* 2018年7月24日			| V1.0.0	| Joker				| Create file
*======================================================================
* Detailed Notes:
*---------------------------------------------------------------------
* <Version>		| <Description>
*---------------------------------------------------------------------
* V1.0.0		| TODO
*---------------------------------------------------------------------

**********************************************************************/

#ifndef UTILS_INC_FIFO_H_
#define UTILS_INC_FIFO_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define		FIFO_SIZE		(sizeof(int32_t) * 4096) //必须为2的幂次

typedef struct fifo
{
    uint8_t buffer[FIFO_SIZE];
    uint32_t in; 			/* 输入指针,必须为uint32_t类型*/
    uint32_t out; 			/* 输出指针，必须为uint32_t类型*/
    uint32_t size;			/* 缓冲区大小，必须为2的次幂*/
}fifo_type;

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

void fifo_init(fifo_type *fifo);
uint16_t fifo_put(fifo_type* fifo, const uint8_t *dat, uint16_t len);
uint8_t fifo_put_byte(fifo_type *fifo, const uint8_t dat);
uint16_t fifo_get(fifo_type* fifo, uint8_t *dat, uint16_t len);
uint16_t fifo_get_only(fifo_type* fifo, uint8_t *dat, uint16_t len);
uint16_t fifo_get_element_size(fifo_type *fifo);
void fifo_clear(fifo_type *fifo);
void fifo_clear_bytes(fifo_type *fifo, uint16_t len);
uint32_t roundup_pow_of_two(uint32_t x);


#endif /* UTILS_INC_FIFO_H_ */
