/*
 * serial_debug.h
 *
 *  Created on: Jun 1, 2018
 *      Author: truongcongtri
 */

#ifndef APP_INC_SERIAL_DEBUG_H_
#define APP_INC_SERIAL_DEBUG_H_

/* Define TINY_PRINTF to use tinyprintf lib */
#define TINY_PRINTF
/* Define SERIAL_DEBUG */
#define SERIAL_DEBUG


#ifdef SERIAL_DEBUG
/* Using tiny printf library */
#ifdef TINY_PRINTF
#include "tinyprintf.h"
#define SERIAL_LOG(...)			tfp_printf(__VA_ARGS__)
#else
/* Using GCC retarget printf library */
#define SERIAL_LOG(...)			printf(__VA_ARGS__);
#endif
#else
#define SERIAL_LOG(...)			do {} while(0);
#endif

#define SLOG_INFO(...)			do { SERIAL_LOG("[INFO ]: "); SERIAL_LOG(__VA_ARGS__); SERIAL_LOG("\r\n"); } while(0);
#define SLOG_DEBUG(...)			do { SERIAL_LOG("[DEBUG]: "); SERIAL_LOG(__VA_ARGS__); SERIAL_LOG("\r\n"); } while(0);
#define SLOG_ERROR(...)			do { SERIAL_LOG("[ERROR]: "); SERIAL_LOG(__VA_ARGS__); SERIAL_LOG("\r\n"); } while(0);
#define SLOG_WARN(...)			do { SERIAL_LOG("[WARN ]: "); SERIAL_LOG(__VA_ARGS__); SERIAL_LOG("\r\n"); } while(0);

typedef enum
{
	BAUD_9600 = 9600,
	BAUD_19200 = 19200,
	BAUD_38400 = 38400,
	BAUD_57600 = 57600,
	BAUD_115200 = 115200
}serial_baud_t;

void serial_debug_init(serial_baud_t baud);

void serial_putc(char c);
void serial_puts(char *str);

char serial_getc(void);
void serial_gets(char *str, int len);



#endif /* APP_INC_SERIAL_DEBUG_H_ */
