#ifndef __APP_UART_CONTROL_H
#define __APP_UART_CONTROL_H

#include "main.h"
#include "app.h"

#define UART_HIGH_BAUD   1
#define UART_LOW_BAUD    2
#define UART_CONTROL_OFF 0

void app_uart_control_init(void);
void app_uart_control(void);

#endif
