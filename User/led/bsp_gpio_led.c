/**
 ******************************************************************************
 * @file     bsp_gpio_led.c
 * @author   embedfire
 * @version  V1.0
 * @date     2024
 * @brief    led应用接口
 ******************************************************************************
 * @attention
 *
 * 实验平台：野火 ebf_py32f002b PY32开发板
 * 论坛      ：http://www.firebbs.cn
 * 官网      ：https://embedfire.com/
 * 淘宝      ：https://yehuosm.tmall.com/
 *
 ******************************************************************************
 */
#include "led/bsp_gpio_led.h"

/**
 * @brief  LED初始化
 * @param  无
 * @note  	无
 * @retval 无
 */
void Bsp_Led_Init(void){
    GPIO_InitTypeDef GPIO_Led_InitConfig;

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_Led_InitConfig.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_Led_InitConfig.Pull  = GPIO_PULLUP;
    GPIO_Led_InitConfig.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_Led_InitConfig.Pin = PWM_GPIO_PIN;
    HAL_GPIO_Init(PWM_GPIO_PORT, &GPIO_Led_InitConfig); /* LED2 GPIO初始化 */

    PWM_LED(LED_OFF);
}

// void Bsp_Led_Init(void)
// {
//     GPIO_InitTypeDef GPIO_Led_InitConfig;

//     LED2_GPIO_CLK_ENABLE(); /* GPIOA时钟使能 */
//     LED3_GPIO_CLK_ENABLE();
//     LED4_GPIO_CLK_ENABLE();

//     GPIO_Led_InitConfig.Mode  = GPIO_MODE_OUTPUT_PP;
//     GPIO_Led_InitConfig.Pull  = GPIO_PULLUP;
//     GPIO_Led_InitConfig.Speed = GPIO_SPEED_FREQ_HIGH;

//     GPIO_Led_InitConfig.Pin = LED2_GPIO_PIN;
//     HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_Led_InitConfig); /* LED2 GPIO初始化 */

//     GPIO_Led_InitConfig.Pin = LED3_GPIO_PIN;
//     HAL_GPIO_Init(LED3_GPIO_PORT, &GPIO_Led_InitConfig); /* LED3 GPIO初始化 */

//     GPIO_Led_InitConfig.Pin = LED4_GPIO_PIN;
//     HAL_GPIO_Init(LED4_GPIO_PORT, &GPIO_Led_InitConfig); /* LED4 GPIO初始化 */

//     LED2(LED_OFF); /* LED 关闭 */
//     LED3(LED_OFF);
//     LED4(LED_OFF);
// }
