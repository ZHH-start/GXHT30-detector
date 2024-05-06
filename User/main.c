/**
 ******************************************************************************
 * @file     main.c
 * @author   embedfire
 * @version  V1.0
 * @date     2024
 * @brief    OLED����
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
#include "main.h"

/**
 * @brief  ������
 * @param  ��
 * @note  	��
 * @retval ��
 */
int main(void)
{
    HAL_Init(); /* HAL���ʼ�� */

    ft temperature; // temperature [��C]
    ft humidity;    // relative humidity [%RH]
    etError error;  // error code

    Bsp_Led_Init();             /* LED ��ʼ�� */
    DEBUG_USART_Config(115200); // UART��ʼ�� A6-TX A7-RX
    SHT3X_Init(0x44);

    error=SHT3X_GetTempAndHumi(&temperature, &humidity, REPEATAB_MEDIUM, MODE_CLKSTRETCH, 50);
    printf("temperature=%.1f\thumidity=%.1f%%RH\terror=%d\r\n",(float)temperature,(float)humidity,(uint8_t)error);

    while (1) {
        HAL_Delay(1000);
    }
}

/*********************************************END OF FILE**********************/
