#ifndef __APP_LED_H
#define __APP_LED_H

#include "main.h"
#include "app.h"

#define PWM_GPIO_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE
#define PWM_GPIO_PORT       GPIOA
#define PWM_GPIO_PIN        GPIO_PIN_1

#define PWM_LED_TOGGLE()    HAL_GPIO_TogglePin(PWM_GPIO_PORT, PWM_GPIO_PIN)

#define PWM_LED(x)          x ? HAL_GPIO_WritePin(PWM_GPIO_PORT, PWM_GPIO_PIN, GPIO_PIN_SET) : HAL_GPIO_WritePin(PWM_GPIO_PORT, PWM_GPIO_PIN, GPIO_PIN_RESET);

#define		LED_ON 		0
#define		LED_OFF 	1

void app_led_init(void);
void app_led_toggle(void);

#endif
