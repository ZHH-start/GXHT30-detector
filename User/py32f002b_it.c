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
#include "Task.h"

/* Private includes ----------------------------------------------------------*/
// #include "command_list.h"
#include "string.h"
#include "bsp_usart.h"
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
    Task_Marks_Handler_Callback();
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

    if (__HAL_UART_GET_FLAG(&Uart1_Handle, UART_FLAG_RXNE)) { // ���ռĴ����ǿ�

        res = READ_REG(Uart1_Handle.Instance->DR); // �����ַ�

        if (Rx_Data_Buf.Is_Reseive_Use_Done == 0) {          // ����ƥ�䴦����ɲ��ܽ����������
            if (res != '\n') {                               // ����֮ǰ
                if (Rx_Data_Buf.Index == Rx_Data_Buf_Size) { // ��������������ͷ��ʼ
                    Rx_Data_Buf.Index = 0;
                }
                Rx_Data_Buf.data[Rx_Data_Buf.Index++] = res; // ��ȡ����
            } else {                                         // ����Ѿ����˻��з�����ʾ������ɡ�
                Rx_Data_Buf.data[Rx_Data_Buf.Index++] = res; // ���д��һ������
                Rx_Data_Buf.Is_Reseive_Use_Done       = 1;   // ���ձ�־λ�ر�
            }
        }
    }

    // /* �����ж� */
    if (__HAL_UART_GET_FLAG(&Uart1_Handle, UART_FLAG_IDLE)) {

        // ���������������������������������������������������������������������������������������������������������������������������������������ڲ�����
        if (strcmp(COMMAND_UART_LOW, Rx_Data_Buf.data) == 0) {
            printf("OK\r\n");
            uart_control = UART_LOW_BAUD;
        }

        else if (strcmp(COMMAND_UART_HIGH, Rx_Data_Buf.data) == 0) {
            printf("OK\r\n");
            uart_control = UART_HIGH_BAUD;
        }

        // �����������������������������������������������������������������������������������������������������������������������������¶ȷ���
        else if (strcmp(COMMAND_SEND_TEMP_ONCE, Rx_Data_Buf.data) == 0) {
            printf("OK\r\n");
            temp_send_speed = TEMP_SEND_ONCE;
        }

        else if (strcmp(COMMAND_SEND_TEMP_LOWSPEED, Rx_Data_Buf.data) == 0) {
            printf("OK\r\n");
            temp_send_speed = TEMP_SEND_LOW_SPEED;
        }

        else if (strcmp(COMMAND_SEND_TEMP_MEDIUMSPEED, Rx_Data_Buf.data) == 0) {
            printf("OK\r\n");
            temp_send_speed = TEMP_SEND_MEDIUM_SPEED;
        }

        else if (strcmp(COMMAND_SEND_TEMP_HIGHSPEED, Rx_Data_Buf.data) == 0) {
            printf("OK\r\n");
            temp_send_speed = TEMP_SEND_HIGH_SPEED;
        }

        else if (strcmp(COMMAND_SEND_TEMP_OFF, Rx_Data_Buf.data) == 0) {
            printf("OK\r\n");
            temp_send_speed = TEMP_SEND_OFF;
        }

        // ������������������������������������������������������������������������������������������������������������������������ʪ�ȷ���
        else if (strcmp(COMMAND_SEND_HUMI_ONCE, Rx_Data_Buf.data) == 0) {
            printf("OK\r\n");
            humi_send_speed = HUMI_SEND_ONCE;
        }

        else if (strcmp(COMMAND_SEND_HUMI_LOWSPEED, Rx_Data_Buf.data) == 0) {
            printf("OK\r\n");
            humi_send_speed = HUMI_SEND_LOW_SPEED;
        }

        else if (strcmp(COMMAND_SEND_HUMI_MEDIUMSPEED, Rx_Data_Buf.data) == 0) {
            printf("OK\r\n");
            humi_send_speed = HUMI_SEND_MEDIUM_SPEED;
        }

        else if (strcmp(COMMAND_SEND_HUMI_HIGHSPEED, Rx_Data_Buf.data) == 0) {
            printf("OK\r\n");
            humi_send_speed = HUMI_SEND_HIGH_SPEED;
        }

        else if (strcmp(COMMAND_SEND_HUMI_OFF, Rx_Data_Buf.data) == 0) {
            printf("OK\r\n");
            humi_send_speed = HUMI_SEND_OFF;
        }

        else {
            printf("ERROR\r\n");
        }
        //     else if (strcmp(COMMAND_4, Rx_Data_Buf.data) == 0) {
        //         command = 4;
        //         printf("OK\r\n");
        //     }
        //     else if (strcmp(COMMAND_5, Rx_Data_Buf.data) == 0) {
        //         command = 5;
        //         printf("OK\r\n");
        //     }
        //     else if (strcmp(COMMAND_6, Rx_Data_Buf.data) == 0) {
        //         command = 6;
        //         printf("OK\r\n");
        //     }
        //     else if (strcmp(COMMAND_7, Rx_Data_Buf.data) == 0) {
        //         command = 7;
        //         printf("OK\r\n");
        //     }
        //     // } else if (strcmp(COMMAND_8, Rx_Data_Buf.data) == 0) {
        //     //     command = 8;
        //     //     printf("OK\r\n");
        //     // }

        //     // printf("Index:%d\r\nRx_Data:%s\r\n", Rx_Data_Buf.Index, Rx_Data_Buf.data);

        Rx_Data_Buf.Is_Reseive_Use_Done = 0; // ����ƥ����ɣ����ձ�־λ��
        Rx_Data_Buf.Index               = 0; // ������ȱ�־

        memset(Rx_Data_Buf.data, 0, Rx_Data_Buf_Size); // ��ս��ջ�����

        __HAL_UART_CLEAR_IDLEFLAG(&Uart1_Handle);
    }
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
