#ifndef __BSP_GPIO_LED_H
#define __BSP_GPIO_LED_H

/* 包含其他头文件 */
#include "py32f0xx_hal.h"

 
/* 宏定义 */
#define		PWM_GPIO_CLK_ENABLE		__HAL_RCC_GPIOA_CLK_ENABLE
#define		PWM_GPIO_PORT				GPIOA
#define		PWM_GPIO_PIN				GPIO_PIN_1

// #define		LED2_GPIO_CLK_ENABLE		__HAL_RCC_GPIOA_CLK_ENABLE
// #define		LED2_GPIO_PORT				GPIOA
// #define		LED2_GPIO_PIN				GPIO_PIN_1

#define		LED3_GPIO_CLK_ENABLE		__HAL_RCC_GPIOA_CLK_ENABLE
#define		LED3_GPIO_PORT				GPIOA
#define		LED3_GPIO_PIN				GPIO_PIN_5

#define		LED4_GPIO_CLK_ENABLE		__HAL_RCC_GPIOA_CLK_ENABLE
#define		LED4_GPIO_PORT				GPIOA
#define		LED4_GPIO_PIN				GPIO_PIN_4

#define		LED_ON 		0
#define		LED_OFF 	1

// #define 	LED2(x)   					x ? \
//                                                         HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_GPIO_PIN, GPIO_PIN_SET): \
//                                                         HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_GPIO_PIN, GPIO_PIN_RESET); \

// #define 	LED2_TOGGLE()     HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_GPIO_PIN)

#define 	PWM_LED(x)   					x ? \
                                                        HAL_GPIO_WritePin(PWM_GPIO_PORT, PWM_GPIO_PIN, GPIO_PIN_SET): \
                                                        HAL_GPIO_WritePin(PWM_GPIO_PORT, PWM_GPIO_PIN, GPIO_PIN_RESET); \

#define 	PWM_LED_TOGGLE()     HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_GPIO_PIN)


#define 	LED3(x)   					x ? \
                                                        HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_GPIO_PIN, GPIO_PIN_SET): \
                                                        HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_GPIO_PIN, GPIO_PIN_RESET); \

#define 	LED3_TOGGLE()     HAL_GPIO_TogglePin(LED3_GPIO_PORT, LED3_GPIO_PIN)


#define 	LED4(x)   					x ? \
                                                        HAL_GPIO_WritePin(LED4_GPIO_PORT, LED4_GPIO_PIN, GPIO_PIN_SET): \
                                                        HAL_GPIO_WritePin(LED4_GPIO_PORT, LED4_GPIO_PIN, GPIO_PIN_RESET); \

#define 	LED4_TOGGLE()     HAL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_GPIO_PIN)

/* 全局变量声明 */


/* 函数声明 */
void Bsp_Led_Init(void);




#endif /* __BSP_GPIO_LED_H */

