#include "stdint.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "nucleo_io.h"
#include "timer_tick.h"
#include "serial_debug.h"

void osc_freq_check(void)
{
  RCC_ClocksTypeDef   RCC_Clock;
  uint8_t Clock_soucre=0;

  /* get clock freq */
  RCC_GetClocksFreq(&RCC_Clock);

  /* get clock source */
  Clock_soucre = RCC_GetSYSCLKSource();

  /* print values to console */
  SLOG_INFO("\n\r");
  SLOG_INFO("====================================================");
  SLOG_INFO("|              TEST Oscillator Clock               |");
  SLOG_INFO("====================================================");
  SLOG_INFO("SYSCLK Freq      : %u",(unsigned int)RCC_Clock.SYSCLK_Frequency);
  SLOG_INFO("HCLK Freq  (AHB) : %u",(unsigned int)RCC_Clock.HCLK_Frequency);
  SLOG_INFO("PCLK1 Freq (APB1): %u",(unsigned int)RCC_Clock.PCLK1_Frequency);
  SLOG_INFO("PCLK2 Freq (APB2): %u",(unsigned int)RCC_Clock.PCLK2_Frequency);
  SLOG_INFO("System Core Clock: %u",(unsigned int)SystemCoreClock);
  SLOG_INFO("Clock source     : %u",(unsigned int)Clock_soucre);
  switch(Clock_soucre)
  {
    case 0:  SLOG_INFO("HSI used as system clock"); break;
    case 4:  SLOG_INFO("HSE used as system clock"); break;
    case 8:  SLOG_INFO("PLL used as system clock"); break;
  }

  SERIAL_LOG("\n\n\r");
}

void serial_log_print(uint8_t type, const char *fmt, ...)
{

}


int main(void)
{
	timer_tick_init();
	serial_debug_init(BAUD_115200);
	nuc_led_init();
	nuc_button_init();

	timer_tick_delay_ms(100);
	osc_freq_check();
	int i = 0;
	int btn_cnt = 0;

	for(;;)
	{
//		SLOG_INFO("Counter: %d", i++);
//		SLOG_INFO("On led");
//		GPIO_SetBits(GPIOA, GPIO_Pin_5);
//		timer_tick_delay_ms(1000u);
//		SLOG_INFO("Off led");
//		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
//		timer_tick_delay_ms(1000u);

		if(nuc_button_status())
		{
			btn_cnt++;
			SLOG_INFO("Button pressed %d", btn_cnt);
		}
	}

	return 0;
}

void assert_failed(uint8_t* file, uint32_t line)
{
	SLOG_ERROR("File: %s - Line: %d: asert failed", file, line);
	while(1)
		;
}
