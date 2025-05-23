#include "main.h"

/**
 * @brief  主函数
 * @param  无
 * @note  	无
 * @retval 无
 */
int main(void)
{
    HAL_Init(); /* HAL库初始化 */

    Bsp_Led_Init();                 /* LED 初始化 */
    DEBUG_USART_Config(115200);       // UART初始化 A6-TX A7-RX
    Rx_Data_Buf_Init(&Rx_Data_Buf); /* USART 接收数据缓冲区初始化 */

    PWM_LED(LED_ON);

    sensirion_i2c_hal_init();
    sht3x_init(SHT30_I2C_ADDR_44);

    printf("MPT-SHT30-WIRE01 ready\r\n");

    while (1) {
        command_run();
    }
}

/*********************************************END OF FILE**********************/
