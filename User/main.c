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

    ft temperature; // temperature [°C]
    ft humidity;    // relative humidity [%RH]
    etError error;  // error code

    Bsp_Led_Init();             /* LED 初始化 */
    DEBUG_USART_Config(115200); // UART初始化 A6-TX A7-RX
    SHT3X_Init(0x44);

    error=SHT3X_GetTempAndHumi(&temperature, &humidity, REPEATAB_MEDIUM, MODE_CLKSTRETCH, 50);
    printf("temperature=%.1f\thumidity=%.1f%%RH\terror=%d\r\n",(float)temperature,(float)humidity,(uint8_t)error);

    while (1) {
        HAL_Delay(1000);
    }
}

/*********************************************END OF FILE**********************/
