#include "stdint.h"
#include "stdio.h"
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

__IO uint32_t delay_time;

void systick_delay_ms(__IO uint32_t time)
{
	delay_time = time;
	while(delay_time == 0)
		;
}

void SysTick_Handler(void)
{
	if(delay_time)
		delay_time--;
}

void delay_ms(__IO uint32_t time)
{
	uint32_t i = 0, j = 0;

	for(i = 0; i < time; i++)
	{
		j = 0xfff;
		while(j--)
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
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == 0)
			;
		str++;
	}
}

void gpio_button_init(void)
{
	GPIO_InitTypeDef gpio_led_cfg;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	gpio_led_cfg.GPIO_Mode = GPIO_Mode_OUT;
	gpio_led_cfg.GPIO_OType = GPIO_OType_PP;
	gpio_led_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_led_cfg.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_led_cfg.GPIO_Pin = GPIO_Pin_13;

	GPIO_Init(GPIOC, &gpio_led_cfg);
}

uint8_t button_status(void)
{
	return 0;
}

void gpio_led_init(void)
{
	GPIO_InitTypeDef gpio_led_cfg;

	gpio_led_cfg.GPIO_Mode = GPIO_Mode_OUT;
	gpio_led_cfg.GPIO_OType = GPIO_OType_PP;
	gpio_led_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_led_cfg.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_led_cfg.GPIO_Pin = GPIO_Pin_5;

	GPIO_Init(GPIOA, &gpio_led_cfg);
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction) 0);
}

void systick_init(void)
{
	SysTick_Config(SystemCoreClock / 1000);
}

int main(void)
{
	SystemInit();
	systick_init();
	uart_debug_init();
	gpio_led_init();
	systick_delay_ms(100);
	for(;;)
	{
		uart_puts("On led\n\r");
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		systick_delay_ms(1000);
		uart_puts("Off led\n\r");
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		systick_delay_ms(1000);
	}

	return 0;
}

void assert_failed(uint8_t* file, uint32_t line)
{
	while(1)
		;
}
