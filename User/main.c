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
#include "led/bsp_gpio_led.h"
#include "usart/bsp_usart_debug.h"
#include "iic/bsp_iic_oled.h"

/**
 * @brief  主函数
 * @param  无
 * @note  	无
 * @retval 无
 */
int main(void)
{
    HAL_Init(); /* HAL库初始化 */

    Bsp_Led_Init(); /* LED 初始化 */

    Bsp_IIC_Init();

    // OLED_Init(); // 初始化OLED

    // OLED_Fill(0xFF); // 全屏点亮

    // unsigned char i;
    while (1) {
        // OLED_Fill(0xFF);//全屏点亮
        // HAL_Delay(1000);		// 1s

        // OLED_Fill(0x00);//全屏灭
        // HAL_Delay(1000);		// 1s

        // for(i=0;i<4;i++)
        // {
        // 	OLED_ShowCN(22+i*16,0,i);									//测试显示中文
        // }

        // HAL_Delay(2000);		// 1s
        // OLED_ShowStr(0,3,(unsigned char*)"Wildfire Tech",1);				//测试6*8字符
        // OLED_ShowStr(0,4,(unsigned char*)"Hello wildfire",2);				//测试8*16字符
        // HAL_Delay(1000);
        // OLED_CLS();//清屏
        // OLED_OFF();//测试OLED休眠
        // HAL_Delay(1000);		// 1s
        // OLED_ON();//测试OLED休眠后唤醒
    }
}

/*********************************************END OF FILE**********************/
