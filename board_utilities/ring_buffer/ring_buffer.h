/*
 * ring_buffer.h
 *
 *  Created on: Mar 7, 2019
 *      Author: congtri
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <string.h>

typedef enum
{
	NO_ERROR,
	WRITE_SIZE_ERROR,
	READ_SIZE_ERROR
}ring_buffer_status_te;

typedef struct
{
	const uint8_t *p_buf;
	const uint8_t *pc_start;
	const uint8_t *pc_end;
	uint8_t *p_read;
	uint8_t *p_write;
	int size;
	int rest_space;
	int real_space;
} ring_buffer_ts;


void initRingBuffer(ring_buffer_ts *ring_buf, uint8_t *element_data, int element_size);
ring_buffer_status_te writeToRingBuffer(ring_buffer_ts *rbuf, const char *data, int len, uint8_t overwrite);
ring_buffer_status_te readFromRingBuffer(ring_buffer_ts *rbuf, uint8_t *data, int len);

#ifdef __cplusplus
}
#endif

#endif /* RING_BUFFER_H_ */
