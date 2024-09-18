#include "app_uart_control.h"
#include "bsp_usart.h"

uint32_t uart_control = UART_CONTROL_OFF;

void app_uart_control_init(void)
{
    DEBUG_USART_Config(115200);
}

void app_uart_control(void)
{
    // printf("choose uart baud\r\n");
    if (uart_control == UART_LOW_BAUD) {
        DEBUG_USART_Config(9600);
        uart_control = UART_CONTROL_OFF;
    }
    if (uart_control == UART_MEDIUM_BAUD) {
        DEBUG_USART_Config(115299);
        uart_control = UART_CONTROL_OFF;
    }
    if (uart_control == UART_HIGH_BAUD) {
        DEBUG_USART_Config(921600);
        uart_control = UART_CONTROL_OFF;
    }
}
