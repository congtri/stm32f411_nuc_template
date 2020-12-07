/*
 * ring_buffer.c
 *
 *  Created on: Mar 7, 2019
 *      Author: congtri
 */
#include "ring_buffer.h"

void write_data(ring_buffer_ts *rbuf, const char *data, int len)
{
	if(rbuf->p_write + len < rbuf->pc_end)
	{
		memcpy(rbuf->p_write, data, len);
		rbuf->p_write += len;
	}
	else
	{
		int part1 = rbuf->pc_end - rbuf->p_write;
		int part2 = len - part1;
		memcpy((void * )rbuf->p_write, (void * )data, part1);
		memcpy((void * )rbuf->pc_start, (void * )data + part1, part2);
		rbuf->p_write = (uint8_t *) rbuf->pc_start + part2;
	}
}

void initRingBuffer(ring_buffer_ts *ring_buf, uint8_t *element_data, int element_size)
{
	memset(element_data, '-', element_size);
	ring_buf->p_buf = element_data;
	ring_buf->pc_start = element_data;
	ring_buf->pc_end = element_data + element_size;
	ring_buf->p_read = (uint8_t *) ring_buf->pc_start;
	ring_buf->p_write = (uint8_t *) ring_buf->pc_start;
	ring_buf->size = element_size;
	ring_buf->rest_space = element_size;
	ring_buf->real_space = element_size - 1;
}

ring_buffer_status_te writeToRingBuffer(ring_buffer_ts *rbuf, const char *data, int len, uint8_t overwrite)
{
	/* Old data will not be overwritten */
	if(!overwrite && len <= rbuf->real_space)
	{
		write_data(rbuf, data, len);
		rbuf->rest_space -= len;
		rbuf->real_space = rbuf->rest_space - 1;

		return NO_ERROR;
	}
	/* Old data will be overwritten by new data */
	else if(overwrite && len <= rbuf->size - 1)
	{
		write_data(rbuf, data, len);
		rbuf->rest_space -= len;
		rbuf->real_space = rbuf->rest_space - 1;

		/* overlap data */
		if(rbuf->rest_space <= 0 || rbuf->real_space < 0)
		{
			rbuf->rest_space = 1;
			rbuf->real_space = 0;
			/* reset data at write pointer location */
			// memset(rbuf->p_write, '-', 1);
			/* update read pointer base on write pointer, this case is applied when overwrite data happen */
			rbuf->p_read = rbuf->p_write + 1;
			if(rbuf->p_read > rbuf->pc_end)
			{
				rbuf->p_read = (uint8_t *) rbuf->pc_start;
			}
		}

		return NO_ERROR;
	}
	else
	{
		/* Cannot write, error happen */
		return WRITE_SIZE_ERROR;
	}
}

ring_buffer_status_te readFromRingBuffer(ring_buffer_ts *rbuf, uint8_t *data, int len)
{
	int available_data = rbuf->size - rbuf->rest_space;

	if(available_data)
	{
		if(rbuf->p_read + len <= rbuf->pc_end)
		{
			memcpy(data, rbuf->p_read, len);
			// memset((uint8_t * )rbuf->p_read, '-', len);
			rbuf->p_read += len;
			if(rbuf->p_read > rbuf->pc_end) rbuf->p_read = (uint8_t*) rbuf->pc_start;
		}
		else
		{
			int part1 = rbuf->pc_end - rbuf->p_read;
			int part2 = len - part1;
			memcpy((uint8_t * )data, rbuf->p_read, part1);
			memcpy((uint8_t * )data + part1, rbuf->pc_start, part2);

			// memset((uint8_t * )rbuf->p_read, '-', part1);
			// memset((uint8_t * )rbuf->pc_start, '-', part2);
			rbuf->p_read = (uint8_t *) rbuf->pc_start + part2;
		}
		rbuf->rest_space += len;
		rbuf->real_space = rbuf->rest_space - 1;

		return NO_ERROR;
	}
	else
	{
		return READ_SIZE_ERROR;
	}
}

int isRingBufferDataAvailable(ring_buffer_ts *rbuf)
{
	return (rbuf->size - rbuf->rest_space);
}
