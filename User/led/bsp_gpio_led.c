/**
 ******************************************************************************
 * @file     bsp_gpio_led.c
 * @author   embedfire
 * @version  V1.0
 * @date     2024
 * @brief    ledӦ�ýӿ�
 ******************************************************************************
 * @attention
 *
 * ʵ��ƽ̨��Ұ�� ebf_py32f002b PY32������
 * ��̳      ��http://www.firebbs.cn
 * ����      ��https://embedfire.com/
 * �Ա�      ��https://yehuosm.tmall.com/
 *
 ******************************************************************************
 */
#include "led/bsp_gpio_led.h"

/**
 * @brief  LED��ʼ��
 * @param  ��
 * @note  	��
 * @retval ��
 */
void Bsp_Led_Init(void){
    GPIO_InitTypeDef GPIO_Led_InitConfig;

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_Led_InitConfig.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_Led_InitConfig.Pull  = GPIO_PULLUP;
    GPIO_Led_InitConfig.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_Led_InitConfig.Pin = PWM_GPIO_PIN;
    HAL_GPIO_Init(PWM_GPIO_PORT, &GPIO_Led_InitConfig); /* LED2 GPIO��ʼ�� */

    PWM_LED(LED_OFF);
}

// void Bsp_Led_Init(void)
// {
//     GPIO_InitTypeDef GPIO_Led_InitConfig;

//     LED2_GPIO_CLK_ENABLE(); /* GPIOAʱ��ʹ�� */
//     LED3_GPIO_CLK_ENABLE();
//     LED4_GPIO_CLK_ENABLE();

//     GPIO_Led_InitConfig.Mode  = GPIO_MODE_OUTPUT_PP;
//     GPIO_Led_InitConfig.Pull  = GPIO_PULLUP;
//     GPIO_Led_InitConfig.Speed = GPIO_SPEED_FREQ_HIGH;

//     GPIO_Led_InitConfig.Pin = LED2_GPIO_PIN;
//     HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_Led_InitConfig); /* LED2 GPIO��ʼ�� */

//     GPIO_Led_InitConfig.Pin = LED3_GPIO_PIN;
//     HAL_GPIO_Init(LED3_GPIO_PORT, &GPIO_Led_InitConfig); /* LED3 GPIO��ʼ�� */

//     GPIO_Led_InitConfig.Pin = LED4_GPIO_PIN;
//     HAL_GPIO_Init(LED4_GPIO_PORT, &GPIO_Led_InitConfig); /* LED4 GPIO��ʼ�� */

//     LED2(LED_OFF); /* LED �ر� */
//     LED3(LED_OFF);
//     LED4(LED_OFF);
// }
