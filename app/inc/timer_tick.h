/*
 * timer_tick.h
 *
 *  Created on: May 30, 2018
 *      Author: truongcongtri
 */

#ifndef APP_INC_TIMER_TICK_H_
#define APP_INC_TIMER_TICK_H_

#include "stm32f4xx.h"

void timer_tick_init(void);

void timer_tick_delay_ms(__IO uint32_t time);


#endif /* APP_INC_TIMER_TICK_H_ */
