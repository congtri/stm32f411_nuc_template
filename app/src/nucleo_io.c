/*
 * nucleo_io.c
 *
 *  Created on: Jun 2, 2018
 *      Author: truongcongtri
 */

#include "stdint.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "nucleo_io.h"

void nuc_button_init(void)
{
	GPIO_InitTypeDef gpio_btn_cfg;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	gpio_btn_cfg.GPIO_Mode = GPIO_Mode_IN;
	gpio_btn_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_btn_cfg.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_btn_cfg.GPIO_Pin = NUC_BUTTON_PIN;

	GPIO_Init(NUC_BUTTON_PORT, &gpio_btn_cfg);
}

uint8_t nuc_button_status(void)
{
	static uint8_t pressed = 0;
	static uint32_t debounce_count = 0;
	uint8_t current_status = GPIO_ReadInputDataBit(NUC_BUTTON_PORT, NUC_BUTTON_PIN);

	if (current_status == 0 && (pressed != 1))
	{
		debounce_count++;
		if(debounce_count == 0xffff)
		{
			pressed = 1;
			return pressed;
		}
	}
	else if (current_status == 0 && (pressed == 1))
	{
		return 0;
	}
	else
	{
		if(debounce_count == 0)
		{
			pressed = 0;
		}
		else
		{
			debounce_count--;
		}
	}

	return 0;
}

void nuc_led_init(void)
{
	GPIO_InitTypeDef gpio_led_cfg;

	gpio_led_cfg.GPIO_Mode = GPIO_Mode_OUT;
	gpio_led_cfg.GPIO_OType = GPIO_OType_PP;
	gpio_led_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_led_cfg.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_led_cfg.GPIO_Pin = GPIO_Pin_5;

	GPIO_Init(NUC_LED_PORT, &gpio_led_cfg);
	GPIO_WriteBit(NUC_LED_PORT, NUC_LED_PIN, (BitAction) 0);
}



