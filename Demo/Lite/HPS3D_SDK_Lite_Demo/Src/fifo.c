/**********************************************************************
* COPYRIGHT NOTICE - HYPERSEN TECHNOLOGY
*
* Copyright (c) 2018, Hypersen Technology, Inc.
*
* All rights reserved.
*
*======================================================================
* \file fifo.c
* \brief TODO 无锁循环队列，只能在只有一个生产者和一个消费者的环境中使用
* \author Joker
* \email Joker_Wu@hypersen.com
* \version 1.0.0
* \date 2018年7月24日 上午12:19:06
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

#include "fifo.h"
#include <string.h>

static uint32_t fls(uint32_t x);

uint32_t fls(uint32_t x)
{
	int8_t position;
	uint32_t i;
	if(0 != x)
	{
		for(i=(x >> 1), position = 0; i != 0; ++position)
			i >>= 1;
	}
	else
	{
		position = -1;
	}
	return position + 1;

}

/**
  * @brief	向上取2次幂整数
  * @param[in]	x 	原数据
  * @note	如果输入的是3，则返回4，输入5，返回8，输入10，返回16
  * @see
  * @code
  * @retval	返回输入数据的2次幂整数
  */
uint32_t roundup_pow_of_two(uint32_t x)
{
	return 1UL << fls(x - 1);
}

/**
  * @brief	初始化缓冲区
  * @param[in]	fifo 	缓冲区handler
  * @note
  * @see
  * @code
  * @retval	None
  */
void fifo_init(fifo_type *fifo)
{
	fifo->in = 0;
	fifo->out = 0;
	fifo->size = FIFO_SIZE;
}

/**
  * @brief	写入缓冲区
  * @param[in]	fifo 	缓冲区handler
  * @param[in]	dat		数据数组
  * @param[in]	len		数据字节数
  * @note
  * @see
  * @code
  * @retval	返回实际写入的字节数
  */
uint16_t fifo_put(fifo_type* fifo, const uint8_t *dat, uint16_t len)
{
    /* 当前缓冲区空闲空间*/
	uint16_t l = 0;
    len = min(len, fifo->size - fifo->in + fifo->out);

    /* 当前in位置到buffer末尾的长度*/
    l = min(len, fifo->size - (fifo->in  & (fifo->size - 1)));

    /* 首先复制数据到[in，buffer的末尾]*/
    memcpy(fifo->buffer + (fifo->in & (fifo->size - 1)), dat, l);

    /* 复制剩余的数据（如果有）到[buffer的起始位置,...]	*/
    memcpy(fifo->buffer, dat + l, len - l);

    fifo->in += len; /* 直接加，不作模运算。当溢出时，从buffer的开始位置重新开始*/

    return len;
}

/**
  * @brief	写入一个字节到缓冲区
  * @param[in]	fifo 	缓冲区handler
  * @param[in]	dat		要写入的字节数据
  * @note
  * @see
  * @code
  * @retval	返回实际写入的字节数
  */
uint8_t fifo_put_byte(fifo_type *fifo, const uint8_t dat)
{
	/* 当前缓冲区空闲空间*/
	uint16_t l = 0;
	uint32_t len = min(1, fifo->size - fifo->in + fifo->out);

	/* 当前in位置到buffer末尾的长度*/
	l = min(len, fifo->size - (fifo->in  & (fifo->size - 1)));

	if(l > 0)
	{
		fifo->buffer[fifo->in & (fifo->size - 1)] = dat;
	}
	else
	{
		fifo->buffer[0] = dat;
	}

	fifo->in += 1; /* 直接加，不作模运算。当溢出时，从buffer的开始位置重新开始*/

	return 1;
}

/**
  * @brief	读取缓冲区
  * @param[in]	fifo 	缓冲区handler
  * @param[out]	dat		数据缓冲区
  * @param[in]	len		要读取的数据字节数
  * @note
  * @see
  * @code
  * @retval	返回实际读取的字节数
  */
uint16_t fifo_get(fifo_type* fifo, uint8_t *dat, uint16_t len)
{
    /* 缓冲区中的数据长度*/
	uint16_t l = 0;
	len = min(len, fifo->in - fifo->out);

	/* 首先从[out,buffer end]读取数据*/
	l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));
	memcpy(dat, fifo->buffer + (fifo->out & (fifo->size - 1)), l);

	/* 从[buffer start,...]读取数据*/
	memcpy(dat + l, fifo->buffer, len - l);

	fifo->out += len; /*直接加，不错模运算。溢出后，从buffer的起始位置重新开始*/

	return len;
}

/**
  * @brief	仅读取缓冲区数据，不清除缓冲区的数据
  * @param[in]	fifo 	缓冲区handler
  * @param[out]	dat		数据缓冲区
  * @param[in]	len		要读取的数据字节数
  * @note
  * @see
  * @code
  * @retval	返回实际读取的字节数
  */
uint16_t fifo_get_only(fifo_type* fifo, uint8_t *dat, uint16_t len)
{
    /* 缓冲区中的数据长度*/
	uint16_t l = 0;
	len = min(len, fifo->in - fifo->out);

	/* 首先从[out,buffer end]读取数据*/
	l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));
	memcpy(dat, fifo->buffer + (fifo->out & (fifo->size - 1)), l);

	/* 从[buffer start,...]读取数据*/
	memcpy(dat + l, fifo->buffer, len - l);

	return len;
}

/**
  * @brief	获取已缓冲数据字节数
  * @param[in]	fifo 	缓冲区handler
  * @note
  * @see
  * @code
  * @retval	返回缓冲区内的数据字节数
  */
uint16_t fifo_get_element_size(fifo_type *fifo)
{
	return fifo->in - fifo->out;
}

/**
  * @brief	清除缓冲区
  * @param[in]	fifo 	缓冲区handler
  * @note
  * @see
  * @code
  * @retval	None
  */
void fifo_clear(fifo_type *fifo)
{
	fifo->in = 0;
	fifo->out = 0;
}

/**
  * @brief	清除缓冲区指定字节数
  * @param[in]	fifo 	缓冲区handler
  * @note
  * @see
  * @code
  * @retval	None
  */
void fifo_clear_bytes(fifo_type *fifo, uint16_t len)
{
	fifo->out += len;
}


