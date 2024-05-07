/**
 ******************************************************************************
 * @file    bsp_usart_debug.c
 * @author  embedfire
 * @version V1.0
 * @date    2023-xx-xx
 * @brief   重定向c库printf函数到usart端口
 ******************************************************************************
 * @attention
 *
 * 实验平台：野火 GDF427-霸天虎 GD32开发板
 * 论坛      ：http://www.firebbs.cn
 * 官网      ：https://embedfire.com/
 * 淘宝      ：https://yehuosm.tmall.com/
 *
 ******************************************************************************
 */

#include "usart/bsp_usart_debug.h"

UART_HandleTypeDef Uart1_Handle; /* 串口句柄声明 */
Buffer Rx_Data_Buf;              /* 串口接收数据缓冲区 */

/**
 * @brief       串口X初始化函数
 * @param       baudrate: 波特率, 根据自己需要设置波特率值
 * @note        注意: 必须设置正确的时钟源, 否则串口波特率就会设置异常.
 * @retval      无
 */
void DEBUG_USART_Config(uint32_t BaudRate)
{
    Uart1_Handle.Instance        = USART1;
    Uart1_Handle.Init.BaudRate   = BaudRate;
    Uart1_Handle.Init.WordLength = UART_WORDLENGTH_8B;
    Uart1_Handle.Init.StopBits   = UART_STOPBITS_1;
    Uart1_Handle.Init.Parity     = UART_PARITY_NONE;
    Uart1_Handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    Uart1_Handle.Init.Mode       = UART_MODE_TX_RX;
    /*使能串口 */
    HAL_UART_Init(&Uart1_Handle);
    /*使能串口接收中断 */
    // __HAL_UART_ENABLE_IT(&Uart1_Handle, UART_IT_RXNE);
}

/**
 * @brief       数据接收缓冲区初始化函数
 * @param       Rx_Data_Buf: 缓冲区
 * @note        使用缓冲区之前必须初始化
 * @retval      无
 */
void Rx_Data_Buf_Init(Buffer *Rx_Data_Buf)
{
    Rx_Data_Buf->Index = 0;
    memset(Rx_Data_Buf->data, 0, Rx_Data_Buf_Size);
}

/**
 * @brief  发送一个16位数函数
 * @param  ch:要发送的数据
 * @note   无
 * @retval 无
 */
void Usart_SendString(uint8_t *str)
{
    unsigned int k = 0;
    do {
        HAL_UART_Transmit(&Uart1_Handle, (uint8_t *)(str + k), 1, 1000);
        k++;
    } while (*(str + k) != '\0');
}

///* 加入以下代码, 支持printf函数 */
#if (defined(__CC_ARM)) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
/**
 * @brief  向usart写入一个字符
 * @param  ch
 *         *f
 * @retval the character
 */
int fputc(int ch, FILE *f)
{
    /* 发送一个字节到USART */
    HAL_UART_Transmit(&Uart1_Handle, (uint8_t *)&ch, 1, 1000);

    return (ch);
}

/**
 * @brief  从usart中获取一个字符
 * @param  *f
 * @retval 获取的字节
 */
int fgetc(FILE *f)
{
    int ch;
    HAL_UART_Receive(&Uart1_Handle, (uint8_t *)&ch, 1, 1000);
    return (ch);
}

#elif defined(__ICCARM__)
/**
 * @brief  向usart写入一个字符
 * @param  ch
 *         *f
 * @retval 写入的字节
 */
int putchar(int ch)
{
    /* 发送一个字节到USART */
    HAL_UART_Transmit(&DebugUartHandle, (uint8_t *)&ch, 1, 1000);

    return (ch);
}
#elif defined(__GNUC__)
/**
 * @brief  向usart写入一个字符
 * @param  ch
 * @retval 发送的字节
 */
int __io_putchar(int ch)
{
    /* 发送一个字节到USART */
    HAL_UART_Transmit(&DebugUartHandle, (uint8_t *)&ch, 1, 1000);

    return ch;
}

int _write(int file, char *ptr, int len)
{
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++) {
        __io_putchar(*ptr++);
    }
    return len;
}
#endif
