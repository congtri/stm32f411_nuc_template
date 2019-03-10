#include <stdio.h>
#include <stdarg.h>
#include "log.h"
#include "string.h"
#include "ring_buffer.h"
#include "tinyprintf.h"
#include "serial_debug.h"

#include "FreeRTOS.h"
#include "task.h"

#define LOG_BUF (256)

static char buf[LOG_BUF];
static char buf_[LOG_BUF];
static char l_buf[LOG_BUF];
ring_buffer_ts rlog;
// ----------------------------------------------------------------------------

void log_init(void)
{
	initRingBuffer(&rlog, (uint8_t *) l_buf, LOG_BUF);
}

void taskPrintLog(void *pv)
{
	log_init();
	serial_puts("taskPrintLog init\n\r");
	while(1)
	{
		int len = isRingBufferDataAvailable(&rlog);
		if(len)
		{
			memset(buf_, 0, LOG_BUF);
			readFromRingBuffer(&rlog, (uint8_t *)buf_, len);
			serial_puts(buf_);
		}
		vTaskDelay(10);
	}
}

int log_printf(const char* format, ...)
{
	int ret;
	va_list ap;

	va_start(ap, format);

	memset(buf, 0, LOG_BUF);
	ret = vsnprintf(buf, sizeof(buf), format, ap);

	if(rlog.real_space >= ret && ret > 0)
	{
		writeToRingBuffer(&rlog, buf, ret, 0);
	}

	va_end(ap);
	return ret;
}

// ----------------------------------------------------------------------------
