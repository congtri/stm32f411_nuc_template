/*
 * timer_tick.c
 *
 *  Created on: May 30, 2018
 *      Author: truongcongtri
 */

#include "stdint.h"
#include "stdio.h"
#include "stm32f4xx.h"
#include "timer_tick.h"

static __IO uint32_t timer_tickCount;

void  __attribute__(( weak )) SysTick_Handler(void)
{
	if(timer_tickCount != 0)
		timer_tickCount--;
}

void timer_tick_init(void)
{
	SysTick_Config(SystemCoreClock/1000u);
}

void timer_tick_delay_ms(__IO uint32_t time)
{
	timer_tickCount = time;
	while(timer_tickCount != 0);
}
