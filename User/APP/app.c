#include "app.h"

void sys_init()
{
    app_uart_control_init();
    app_led_init();
    app_sht_read_init();
    app_sht_read();
}