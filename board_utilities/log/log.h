#ifndef LOG_H_
#define LOG_H_

#include <unistd.h>

#if defined(__cplusplus)
extern "C"
{
#endif

	void taskPrintLog(void *pv);
	void trace_initialize(void);
	int log_printf(const char* format, ...);

#if defined(__cplusplus)
}
#endif

// ----------------------------------------------------------------------------

#endif // LOG_H_
