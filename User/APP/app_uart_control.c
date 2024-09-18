#include "app_uart_control.h"
#include "bsp_usart.h"
#include "stdio.h"

__IO int uart_control = UART_CONTROL_OFF;

void app_uart_control_init(void)
{
    DEBUG_USART_Config(115200);
    Rx_Data_Buf_Init(&Rx_Data_Buf); // USART 接收数据缓冲区初始化
}

void app_uart_control(void)
{
    if (uart_control == UART_LOW_BAUD) {
        DEBUG_USART_Config(9600);
        uart_control = UART_CONTROL_OFF;
    } else if (uart_control == UART_HIGH_BAUD) {
        DEBUG_USART_Config(115200);
        uart_control = UART_CONTROL_OFF;
    }
}
