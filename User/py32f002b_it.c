/**
 ******************************************************************************
 * @file    py32f002b_it.c
 * @author  MCU Application Team
 * @brief   Interrupt Service Routines.
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
#include "py32f002b_it.h"

/* Private includes ----------------------------------------------------------*/
#include "usart/bsp_usart_debug.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*          Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void)
{
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
    while (1) {
    }
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void)
{
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void)
{
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void)
{
    HAL_IncTick();
}

/******************************************************************************/
/* PY32F002B Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file.                                          */
/******************************************************************************/
void USART1_IRQHandler(void)
{
    uint8_t res;

    if (__HAL_UART_GET_FLAG(&Uart1_Handle, UART_FLAG_RXNE)) { // 接收寄存器非空

        res = READ_REG(Uart1_Handle.Instance->DR); // 接收字符

        if (Rx_Data_Buf.Is_Reseive_Use_Done == 0) {          // 处理完成才能进入接收流程
            if (res != '\n') {                               // 换行之前
                if (Rx_Data_Buf.Index == Rx_Data_Buf_Size) { // 如果超出长度则从头开始
                    Rx_Data_Buf.Index = 0;
                }
                Rx_Data_Buf.data[Rx_Data_Buf.Index++] = res; // 读取数据
            } else {                                         // 如果已经到了换行符，表示接收完成。
                Rx_Data_Buf.data[Rx_Data_Buf.Index++] = res; // 最后写入一个换行
                Rx_Data_Buf.Is_Reseive_Use_Done       = 1;   // 标志位关闭
            }
        }
        // else
        //     Rx_Data_Buf.Index = 0; // 重置接收
    }

    /* 空闲中断 */
    if (__HAL_UART_GET_FLAG(&Uart1_Handle, UART_FLAG_IDLE)) {
        __HAL_UART_CLEAR_IDLEFLAG(&Uart1_Handle);
        // printf("Index:%d\r\nRx_Data:%s\r\n", Rx_Data_Buf.Index, Rx_Data_Buf.data);

        // Rx_Data_Buf.Is_Reseive_Use_Done = 0; // 标志位打开
        Rx_Data_Buf.Index               = 0; // 清除接收

        memset(Rx_Data_Buf.data, 0, Rx_Data_Buf_Size); // 清空接收缓冲区
    }
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
