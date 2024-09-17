#include "app.h"

#include "bsp_usart_debug.h"

void sys_init()
{
    DEBUG_USART_Config(115200);
    app_led_init();
    app_sht_read_init();
    app_sht_read();
}