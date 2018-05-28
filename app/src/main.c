/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"


void delay_ms(uint32_t time)
{
	uint32_t i, j;

	for(i = 0; i < time; i++)
	{
		for(j = 0; j < 33333; j++)
			;
	}
}

void uart_debug_init(void)
{
	/* USARTx configured as follow:
	 - BaudRate = 115200 baud
	 - Word Length = 8 Bits
	 - One Stop Bit
	 - No parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	 */

	GPIO_InitTypeDef gpio_uart_cfg;
	USART_InitTypeDef uart_cfg;
	NVIC_InitTypeDef uart_nvic_cgf;

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
	uart_cfg.USART_BaudRate = 115200;
	uart_cfg.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart_cfg.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	uart_cfg.USART_Parity = USART_Parity_No;
	uart_cfg.USART_StopBits = USART_StopBits_1;
	uart_cfg.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART2, &uart_cfg);
	/* Enable USART2 Rx interrup */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	/* Config NVIC for Rx */
	uart_nvic_cgf.NVIC_IRQChannel = USART2_IRQn;
	uart_nvic_cgf.NVIC_IRQChannelPreemptionPriority = 0;
	uart_nvic_cgf.NVIC_IRQChannelSubPriority = 0;
	uart_nvic_cgf.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&uart_nvic_cgf);

	/* Enable USART2 */
	USART_Cmd(USART2, ENABLE);
}

void uart_puts(const char *str)
{
	while(*str != 0)
	{
		USART_SendData(USART2, *str);
		/* Loop until data complete tranmission */
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==0);
		str++;
	}
}

void gpio_button_init(void)
{

}

void gpio_led_init(void)
{

}

int main(void)
{
	SystemInit();
	delay_ms(100);
	uart_debug_init();
	delay_ms(100);
	for(;;)
	{
		uart_puts("hello\n\r");
		delay_ms(1000);
	}

	return 0;
}
