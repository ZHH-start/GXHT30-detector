#ifndef __BSP_USART_DEBUG_H
#define __BSP_USART_DEBUG_H

/* 包含其他头文件 */
#include "py32f0xx_hal.h"
#include "stdio.h"
#include "string.h"

/* 宏定义 */
#define DEBUG_UART_Rx_GPIO_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE
#define DEBUG_UART_Rx_GPIO_PORT       GPIOA
#define DEBUG_UART_Rx_GPIO_PIN        GPIO_PIN_7

#define DEBUG_UART_Tx_GPIO_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE
#define DEBUG_UART_Tx_GPIO_PORT       GPIOA
#define DEBUG_UART_Tx_GPIO_PIN        GPIO_PIN_6

#define Rx_Data_Buf_Size              200

typedef struct
{
    uint16_t Index;
    char data[Rx_Data_Buf_Size];
} Buffer;

/* 全局变量声明 */
extern UART_HandleTypeDef Uart1_Handle;
extern Buffer Rx_Data_Buf;

/* 函数声明 */
void Rx_Data_Buf_Init(Buffer *Rx_Data_Buf);
void DEBUG_USART_Config(uint32_t BaudRate);
void Usart_SendString(uint8_t *str);

#endif /* __BSP_USART_DEBUG_H */
