#include "stdint.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "nucleo_io.h"
#include "timer_tick.h"
#include "serial_debug.h"

#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

#define LED_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE )
#define LED_TASK_PRIORITY			( tskIDLE_PRIORITY + 1 )

void osc_freq_check(void)
{
	RCC_ClocksTypeDef RCC_Clock;
	uint8_t Clock_soucre = 0;

	/* get clock freq */
	RCC_GetClocksFreq(&RCC_Clock);

	/* get clock source */
	Clock_soucre = RCC_GetSYSCLKSource();
	/* print values to console */
	printf("\n\r");
	printf("====================================================\n\r");
	printf("|              TEST Oscillator Clock               |\n\r");
	printf("====================================================\n\r");
	printf("SYSCLK Freq      : %u\n\r", (unsigned int )RCC_Clock.SYSCLK_Frequency);
	printf("HCLK Freq  (AHB) : %u\n\r", (unsigned int )RCC_Clock.HCLK_Frequency);
	printf("PCLK1 Freq (APB1): %u\n\r", (unsigned int )RCC_Clock.PCLK1_Frequency);
	printf("PCLK2 Freq (APB2): %u\n\r", (unsigned int )RCC_Clock.PCLK2_Frequency);
	printf("System Core Clock: %u\n\r", (unsigned int )SystemCoreClock);
	printf("Clock source     : %u\n\r", (unsigned int )Clock_soucre);
	switch(Clock_soucre)
	{
		case 0:
			printf("HSI used as system clock\n\r");
			break;
		case 4:
			printf("HSE used as system clock\n\r");
			break;
		case 8:
			printf("PLL used as system clock\n\r");
			break;
	}

	printf("\n\n\r");
}


void vLEDTask(void * pvArg)
{
	nuc_led_init();

	while(1)
	{
		SLOG_INFO("On led");
		nuc_led_set();
		vTaskDelay(100);

		SLOG_INFO("Off led");
		nuc_led_clr();
		vTaskDelay(100);

	}
}

void vLogTask(void * pvArg)
{
	int i = 0;
	while(1)
	{
		SLOG_INFO("Counter 1: [%d]", i);
		int x = xPortGetFreeHeapSize();
		SLOG_INFO("Heap size: %d", x);
		i++;
		vTaskDelay(500);
	}
}

void vLogTask_2(void * pvArg)
{
	int i = 0;
	while(1)
	{
		SLOG_INFO("Counter 2: [%d]", i);
		i++;
		vTaskDelay(50);
	}
}



int main(void)
{
	//timer_tick_init();
	serial_debug_init(BAUD_115200);
	nuc_led_init();
	nuc_button_init();

	//timer_tick_delay_ms(100);
	osc_freq_check();

	xTaskCreate(vLEDTask,
				NULL,
				50,
				NULL,
				LED_TASK_PRIORITY + 1,
				NULL);

	xTaskCreate(vLogTask,
				NULL,
				50,
				NULL,
				LED_TASK_PRIORITY + 4,
				NULL);

	xTaskCreate(vLogTask_2,
					NULL,
					50,
					NULL,
					LED_TASK_PRIORITY + 4,
					NULL);

	xTaskCreate(taskPrintLog,
				NULL,
				50,
				NULL,
				LED_TASK_PRIORITY + 5,
				NULL);

	/* Start the scheduler. */
	vTaskStartScheduler();

	/* Code shouldn't go here */
	printf("FreeRTOS init error");
	while(1);

	return 0;
}

void assert_failed(uint8_t* file, uint32_t line)
{
	printf("File: %s - Line: %d: asert failed", file, (unsigned int )line);
	while(1)
		;
}
