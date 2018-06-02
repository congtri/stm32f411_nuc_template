/*
 * nucleo_io.h
 *
 *  Created on: Jun 2, 2018
 *      Author: truongcongtri
 */

#ifndef APP_INC_NUCLEO_IO_H_
#define APP_INC_NUCLEO_IO_H_

/* Define Led position on Nucleo board */
#define NUC_LED_PIN					GPIO_Pin_5
#define NUC_LED_PORT					GPIOA
#define NUC_BOARD_LED_SET()			GPIO_SetBits(NUC_LED_PORT, NUC_LED_PIN);
#define nuc_led_set()				NUC_BOARD_LED_SET()

#define NUC_BOARD_LED_CLR()			GPIO_ResetBits(NUC_LED_PORT, NUC_LED_PIN);
#define nuc_led_clr()				NUC_BOARD_LED_CLR()

#define NUC_BUTTON_PIN				GPIO_Pin_13
#define NUC_BUTTON_PORT				GPIOC
#define NUC_BOARD_BTN_STATUS()		GPIO_ReadInputDataBit(NUC_BUTTON_PORT, NUC_BUTTON_PIN);

typedef enum
{
	BUTTON_HOLD_MODE,
	BUTTON_CONTINOUES_MODE,
}btn_press_mode_t;

void nuc_button_init(void);
void nuc_led_init(void);

uint8_t nuc_button_status(void);

#endif /* APP_INC_NUCLEO_IO_H_ */
