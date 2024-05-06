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
 * ʵ��ƽ̨��Ұ�� ebf_py32f002b PY32������
 * ��̳      ��http://www.firebbs.cn
 * ����      ��https://embedfire.com/
 * �Ա�      ��https://yehuosm.tmall.com/
 *
 ******************************************************************************
 */
#include "systick/bsp_systick_delay.h"

/* us��ʱ���� */
static uint8_t fac_us = HSI_VALUE / 1000000;

/**
 * @brief   us��ʱ����,1usΪһ����λ
 * @param
 *		@arg nTime: Delay_us( 1 ) ��ʵ�ֵ���ʱΪ 1 * 1us = 1us
 * @retval  ��
 */
void Delay_us(__IO uint32_t nTime)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;  // LOAD��ֵ
    ticks           = nTime * fac_us; // ��Ҫ�Ľ�����
    told            = SysTick->VAL;   // �ս���ʱ�ļ�����ֵ
    while (1) {
        tnow = SysTick->VAL;
        if (tnow != told) {
            if (tnow < told)
                tcnt += told - tnow; // ����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
            else
                tcnt += reload - tnow + told;
            told = tnow;
            if (tcnt >= ticks) break; // ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
        }
    }
}

/**
 * @brief   ms��ʱ����,1msΪһ����λ
 * @param
 *		@arg nTime: Delay_ms( 1 ) ��ʵ�ֵ���ʱΪ 1 * 1ms = 1ms
 * @retval  ��
 */
void Delay_ms(__IO uint32_t nTime)
{
    Delay_us(nTime * 1000);
}

/*********************************************END OF FILE**********************/
