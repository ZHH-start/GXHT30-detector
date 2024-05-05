#ifndef __BSP_EXIT_KEY_H
#define __BSP_EXIT_KEY_H

/* 包含其他头文件 */
#include "py32f0xx_hal.h"
#include "led/bsp_gpio_led.h"

/* 宏定义 */
#define		Key1_GPIO_CLK_ENABLE			__HAL_RCC_GPIOA_CLK_ENABLE
#define		Key1_GPIO_PORT					GPIOA
#define		Key1_GPIO_PIN					GPIO_PIN_0
#define     Key1_IRQ                        EXTI0_1_IRQn
#define     Key1_IRQHandler                 EXTI0_1_IRQHandler

#define		Key2_GPIO_CLK_ENABLE			__HAL_RCC_GPIOA_CLK_ENABLE
#define		Key2_GPIO_PORT					GPIOA
#define		Key2_GPIO_PIN					GPIO_PIN_3
#define     Key2_IRQ                        EXTI2_3_IRQn
#define     Key2_IRQHandler                 EXTI2_3_IRQHandler         
            


/* 全局变量声明 */
extern EXTI_HandleTypeDef key1_exti_handle;
extern EXTI_HandleTypeDef key2_exti_handle;

/* 函数声明 */
void 	Bsp_EXIT_Init(void);
void    Key1_Callback(void);
void    Key2_Callback(void);

#endif /* __BSP_EXIT_KEY_H */

