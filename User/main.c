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

    Bsp_Led_Init();             /* LED 初始化 */
    DEBUG_USART_Config(115200); // UART初始化 A6-TX A7-RX

    Usart_SendString("欢迎使用野火PY32开发板 !!!\r\n");

    printf("test\r\n");

    while (1) {
        HAL_Delay(1000);
    }
}

/*********************************************END OF FILE**********************/
