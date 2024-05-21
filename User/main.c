/**
 ******************************************************************************
 * @file     main.c
 * @author   embedfire
 * @version  V1.0
 * @date     2024
 * @brief    OLED测试
 ******************************************************************************
 * @attention
 *
 * 实验平台：野火 ebf_py32f002b PY32开发板
 * 论坛      ：http://www.firebbs.cn
 * 官网      ：https://embedfire.com/
 * 淘宝      ：https://yehuosm.tmall.com/
 *
 ******************************************************************************
 */
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

    int16_t error = NO_ERROR;
    Bsp_Led_Init();                 /* LED 初始化 */
    DEBUG_USART_Config(115200);     // UART初始化 A6-TX A7-RX
    Rx_Data_Buf_Init(&Rx_Data_Buf); /* USART 接收数据缓冲区初始化 */

    sensirion_i2c_hal_init();
    sht3x_init(SHT30_I2C_ADDR_44);

    // printf("init done");

    int32_t a_temperature = 0;
    int32_t a_humidity    = 0;
    // uint16_t repetition   = 0;

    while (1) {
        // error = sht3x_measure_single_shot(REPEATABILITY_MEDIUM, false, &a_temperature, &a_humidity);
        // if (error != NO_ERROR) {
        //     printf("error executing measure_single_shot(): %i\n", error);
        //     continue;
        // }
        // printf("a_temperature  [milli degC]: %i ", a_temperature);
        // printf("a_humidity  [milli RH]: %i\n", a_humidity);

        // if (Rx_Data_Buf.Is_Reseive_Use_Done == 1) {
        //     printf("Index:%d\r\nRx_Data:%s\r\n", Rx_Data_Buf.Index, Rx_Data_Buf.data);
        //     Rx_Data_Buf.Is_Reseive_Use_Done = 0; // 标志位打开
        //     Rx_Data_Buf.Index               = 0; // 清除接收
        //     memset(Rx_Data_Buf.data, 0, Rx_Data_Buf_Size); // 清空接收缓冲区
        // }
        command_run();
        HAL_Delay(100);
    }
}

/*********************************************END OF FILE**********************/
