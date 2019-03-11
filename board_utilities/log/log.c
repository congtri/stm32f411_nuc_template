#include <stdio.h>
#include <stdarg.h>
#include "log.h"
#include "string.h"
#include "ring_buffer.h"
#include "tinyprintf.h"
#include "serial_debug.h"

#include "FreeRTOS.h"
#include "task.h"

#define LOG_BUF_SIZE		(1024)
#define READ_BUF_SIZE		(128)
#define W_BUF_SIZE			(128)

static char wbuf[LOG_BUF_SIZE];
static char buf_data[LOG_BUF_SIZE];
ring_buffer_ts rlog;
// ----------------------------------------------------------------------------

void log_init(void)
{
	initRingBuffer(&rlog, (uint8_t *)buf_data, LOG_BUF_SIZE);
}

void taskPrintLog(void *pv)
{
	log_init();
	serial_puts("taskPrintLog init\n\r");
	while (1)
	{
		int available_data = rlog.size - rlog.rest_space;

		if (available_data)
		{
			/* Write maximum 128 bytes per each task cyle */
			if(available_data > READ_BUF_SIZE)
			{
				available_data = READ_BUF_SIZE;
			}

			if (rlog.p_read + available_data <= rlog.pc_end)
			{
				serial_put_array(rlog.p_read, available_data);

				rlog.p_read += available_data;
				if (rlog.p_read > rlog.pc_end)
					rlog.p_read = (uint8_t *)rlog.pc_start;
			}
			else
			{
				int part1 = rlog.pc_end - rlog.p_read;
				int part2 = available_data - part1;

				serial_put_array(rlog.p_read, part1);
				serial_put_array(rlog.pc_start, part2);

				rlog.p_read = (uint8_t *)rlog.pc_start + part2;
			}
			rlog.rest_space += available_data;
			rlog.real_space = rlog.rest_space - 1;
		}

		vTaskDelay(10);
	}
}

int log_printf(const char *format, ...)
{
	int ret;
	va_list ap;

	va_start(ap, format);

	memset(wbuf, 0, W_BUF_SIZE);
	ret = vsnprintf(wbuf, sizeof(wbuf), format, ap);

	if (rlog.real_space >= ret && ret > 0)
	{
		writeToRingBuffer(&rlog, wbuf, ret, 0);
	}

	va_end(ap);
	return ret;
}

// ----------------------------------------------------------------------------
