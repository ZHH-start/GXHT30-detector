/**
 ******************************************************************************
 * @file    py32f002b_hal_msp.c
 * @author  MCU Application Team
 * @brief   This file provides code for the MSP Initialization
 *          and de-Initialization codes.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
 * All rights reserved.</center></h2>
 *
 * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "bsp_usart_debug.h"
// #include "bsp_iic_oled.h"
#include "bsp_systick_delay.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* External functions --------------------------------------------------------*/

/**
 * @brief Initialize global MSP.
 */
void HAL_MspInit(void)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
}

/**
 * @brief Initialize MSP for I2C.
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_I2C_CLK_ENABLE();   /* I2C clock enable */
    __HAL_RCC_GPIOB_CLK_ENABLE(); /* GPIOB clock enable */

    GPIO_InitStruct.Pin       = GPIO_PIN_3 | GPIO_PIN_4; // B3-SCL B4-SDA
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;         /* open drain */
    GPIO_InitStruct.Pull      = GPIO_PULLUP;             /* pull up */
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_I2C1; /* Reuse as I2C */
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);    /* GPIO initialization */

    /*Reset I2C*/
    __HAL_RCC_I2C_FORCE_RESET();
    __HAL_RCC_I2C_RELEASE_RESET();
}

/**
 * @brief       UART�ײ��ʼ������
 * @param       huart: UART�������ָ��
 * @note        �˺����ᱻHAL_UART_Init()����
 *              ���ʱ��ʹ�ܣ��������ã��ж�����
 * @retval      ��
 */
void HAL_UART_MspInit(UART_HandleTypeDef *UartHandle)
{
    if (UartHandle->Instance == USART1) {
        GPIO_InitTypeDef Uart_GPIO_InitConfig;

        /*USART1ʱ��ʹ��*/
        DEBUG_UART_Rx_GPIO_CLK_ENABLE();
        DEBUG_UART_Tx_GPIO_CLK_ENABLE();
        __HAL_RCC_USART1_CLK_ENABLE();

        Uart_GPIO_InitConfig.Pin       = DEBUG_UART_Tx_GPIO_PIN; // A6-TX
        Uart_GPIO_InitConfig.Mode      = GPIO_MODE_AF_PP;
        Uart_GPIO_InitConfig.Pull      = GPIO_PULLUP;
        Uart_GPIO_InitConfig.Speed     = GPIO_SPEED_FREQ_HIGH;
        Uart_GPIO_InitConfig.Alternate = GPIO_AF1_USART1; // ���ø���AF1
        HAL_GPIO_Init(DEBUG_UART_Tx_GPIO_PORT, &Uart_GPIO_InitConfig);

        Uart_GPIO_InitConfig.Pin       = DEBUG_UART_Rx_GPIO_PIN; // A7-RX
        Uart_GPIO_InitConfig.Mode      = GPIO_MODE_AF_PP;
        Uart_GPIO_InitConfig.Pull      = GPIO_PULLUP;
        Uart_GPIO_InitConfig.Speed     = GPIO_SPEED_FREQ_HIGH;
        Uart_GPIO_InitConfig.Alternate = GPIO_AF3_USART1; // ���ø���AF3
        HAL_GPIO_Init(DEBUG_UART_Rx_GPIO_PORT, &Uart_GPIO_InitConfig);

        __HAL_UART_ENABLE_IT(&Uart1_Handle, UART_IT_RXNE); /*ʹ�ܴ��ڽ����ж� */
        __HAL_UART_ENABLE_IT(&Uart1_Handle, UART_IT_IDLE); /*ʹ�ܴ��ڽ��տ����ж� */

        HAL_NVIC_SetPriority(USART1_IRQn, 0, 0); /* ��ռ���ȼ�0�������ȼ�0 */
        HAL_NVIC_EnableIRQ(USART1_IRQn);         /* ʹ��USART1�ж�ͨ�� */
    }
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
