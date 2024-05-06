/**
 ******************************************************************************
 * @file     bsp_gpio_led.c
 * @author   embedfire
 * @version  V1.0
 * @date     2024
 * @brief
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
#include "systick/bsp_systick_delay.h"

/* us延时节拍 */
static uint8_t fac_us = HSI_VALUE / 1000000;

/**
 * @brief   us延时程序,1us为一个单位
 * @param
 *		@arg nTime: Delay_us( 1 ) 则实现的延时为 1 * 1us = 1us
 * @retval  无
 */
void Delay_us(__IO uint32_t nTime)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;  // LOAD的值
    ticks           = nTime * fac_us; // 需要的节拍数
    told            = SysTick->VAL;   // 刚进入时的计数器值
    while (1) {
        tnow = SysTick->VAL;
        if (tnow != told) {
            if (tnow < told)
                tcnt += told - tnow; // 这里注意一下SYSTICK是一个递减的计数器就可以了.
            else
                tcnt += reload - tnow + told;
            told = tnow;
            if (tcnt >= ticks) break; // 时间超过/等于要延迟的时间,则退出.
        }
    }
}

/**
 * @brief   ms延时程序,1ms为一个单位
 * @param
 *		@arg nTime: Delay_ms( 1 ) 则实现的延时为 1 * 1ms = 1ms
 * @retval  无
 */
void Delay_ms(__IO uint32_t nTime)
{
    Delay_us(nTime * 1000);
}

/*********************************************END OF FILE**********************/
