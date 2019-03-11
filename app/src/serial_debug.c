/*
 * serial_debug.c
 *
 *  Created on: Jun 1, 2018
 *      Author: truongcongtri
 */

#include "stdint.h"
#include "stdio.h"
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "serial_debug.h"


/* Retartget for USART to use printf function */
/* Using tiny printf library */
#ifdef TINY_PRINTF
#include "tinyprintf.h"

void sputc(void *p, char c)
{
	USART_SendData(USART2, c);
	/* Loop until data complete tranmission */
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == 0);
}
#else
/* Using normal printf GCC to put USART */
int __io_putchar(int ch)
{
	USART_SendData(USART2, ch);
	/* Loop until data complete tranmission */
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == 0);

	return 0;
}

int __io_getchar(void)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
	return USART_ReceiveData(USART2);
}
#endif
/* End of Retarget */


/* Using RX interrupt to receive data from USART */
#ifdef USART_RX_INT
void USART2_IRQHandler(void)
{
	char c = 0;
	while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
	c = USART_ReceiveData(USART2);
}
#endif


void serial_debug_init(serial_baud_t baud)
{
	/* USART2 configured as follow:
	 - BaudRate = 115200 baud
	 - Word Length = 8 Bits
	 - One Stop Bit
	 - No parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	 */

	GPIO_InitTypeDef gpio_uart_cfg;
	USART_InitTypeDef uart_cfg;

	/** USART2 GPIOs Configuration
	 - PA9  --> USART2 Tx
	 - PA10 --> USART2 Rx
	 */

	/* enable clock for GPIO, UART */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* config Tx, Rx Pin */
	gpio_uart_cfg.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart_cfg.GPIO_OType = GPIO_OType_PP;
	gpio_uart_cfg.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_uart_cfg.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_uart_cfg.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIOA, &gpio_uart_cfg);

	/* connect Rx pin to USART2 Rx */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	/* connect Tx pin to USAT1 Tx */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	/* config USART2 */
	uart_cfg.USART_BaudRate = baud;
	uart_cfg.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart_cfg.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	uart_cfg.USART_Parity = USART_Parity_No;
	uart_cfg.USART_StopBits = USART_StopBits_1;
	uart_cfg.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART2, &uart_cfg);

#ifdef USART_RX_INT
	/* Enable USART2 Rx interrup */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	NVIC_InitTypeDef uart_nvic_cgf;
	/* Config NVIC for Rx */
	uart_nvic_cgf.NVIC_IRQChannel = USART2_IRQn;
	uart_nvic_cgf.NVIC_IRQChannelPreemptionPriority = 0;
	uart_nvic_cgf.NVIC_IRQChannelSubPriority = 0;
	uart_nvic_cgf.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&uart_nvic_cgf);
#endif

	/* Enable USART2 */
	USART_Cmd(USART2, ENABLE);

#ifdef TINY_PRINTF
	init_printf(NULL, sputc);
#endif
}


void serial_putc(char c)
{
	USART_SendData(USART2, c);
	/* Loop until data complete tranmission */
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == 0);
}


void serial_puts(char *str)
{
	while(*str != 0)
	{
		USART_SendData(USART2, *str);
		/* Loop until data complete tranmission */
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == 0);

		str++;
	}
}

void serial_put_array(char *arr, int len)
{
	int i = 0;
	while(len)
	{
		USART_SendData(USART2, arr[i]);
		/* Loop until data complete tranmission */
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == 0);
		i++;
		len--;
	}
}

char serial_getc(void)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
	return USART_ReceiveData(USART2);
}


void serial_gets(char *str, int len)
{
	while(len > 0 && str != NULL)
	{
		while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
		*str = USART_ReceiveData(USART2);

		str++;
		len--;
	}
}
