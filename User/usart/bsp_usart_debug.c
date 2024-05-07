/**
 ******************************************************************************
 * @file    bsp_usart_debug.c
 * @author  embedfire
 * @version V1.0
 * @date    2023-xx-xx
 * @brief   �ض���c��printf������usart�˿�
 ******************************************************************************
 * @attention
 *
 * ʵ��ƽ̨��Ұ�� GDF427-���컢 GD32������
 * ��̳      ��http://www.firebbs.cn
 * ����      ��https://embedfire.com/
 * �Ա�      ��https://yehuosm.tmall.com/
 *
 ******************************************************************************
 */

#include "usart/bsp_usart_debug.h"

UART_HandleTypeDef Uart1_Handle; /* ���ھ������ */
Buffer Rx_Data_Buf;              /* ���ڽ������ݻ����� */

/**
 * @brief       ����X��ʼ������
 * @param       baudrate: ������, �����Լ���Ҫ���ò�����ֵ
 * @note        ע��: ����������ȷ��ʱ��Դ, ���򴮿ڲ����ʾͻ������쳣.
 * @retval      ��
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
    /*ʹ�ܴ��� */
    HAL_UART_Init(&Uart1_Handle);
    /*ʹ�ܴ��ڽ����ж� */
    // __HAL_UART_ENABLE_IT(&Uart1_Handle, UART_IT_RXNE);
}

/**
 * @brief       ���ݽ��ջ�������ʼ������
 * @param       Rx_Data_Buf: ������
 * @note        ʹ�û�����֮ǰ�����ʼ��
 * @retval      ��
 */
void Rx_Data_Buf_Init(Buffer *Rx_Data_Buf)
{
    Rx_Data_Buf->Index = 0;
    memset(Rx_Data_Buf->data, 0, Rx_Data_Buf_Size);
}

/**
 * @brief  ����һ��16λ������
 * @param  ch:Ҫ���͵�����
 * @note   ��
 * @retval ��
 */
void Usart_SendString(uint8_t *str)
{
    unsigned int k = 0;
    do {
        HAL_UART_Transmit(&Uart1_Handle, (uint8_t *)(str + k), 1, 1000);
        k++;
    } while (*(str + k) != '\0');
}

///* �������´���, ֧��printf���� */
#if (defined(__CC_ARM)) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
/**
 * @brief  ��usartд��һ���ַ�
 * @param  ch
 *         *f
 * @retval the character
 */
int fputc(int ch, FILE *f)
{
    /* ����һ���ֽڵ�USART */
    HAL_UART_Transmit(&Uart1_Handle, (uint8_t *)&ch, 1, 1000);

    return (ch);
}

/**
 * @brief  ��usart�л�ȡһ���ַ�
 * @param  *f
 * @retval ��ȡ���ֽ�
 */
int fgetc(FILE *f)
{
    int ch;
    HAL_UART_Receive(&Uart1_Handle, (uint8_t *)&ch, 1, 1000);
    return (ch);
}

#elif defined(__ICCARM__)
/**
 * @brief  ��usartд��һ���ַ�
 * @param  ch
 *         *f
 * @retval д����ֽ�
 */
int putchar(int ch)
{
    /* ����һ���ֽڵ�USART */
    HAL_UART_Transmit(&DebugUartHandle, (uint8_t *)&ch, 1, 1000);

    return (ch);
}
#elif defined(__GNUC__)
/**
 * @brief  ��usartд��һ���ַ�
 * @param  ch
 * @retval ���͵��ֽ�
 */
int __io_putchar(int ch)
{
    /* ����һ���ֽڵ�USART */
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
