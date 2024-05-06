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

    Bsp_Led_Init();             /* LED ��ʼ�� */
    DEBUG_USART_Config(115200); // UART��ʼ�� A6-TX A7-RX

    Usart_SendString("��ӭʹ��Ұ��PY32������ !!!\r\n");

    printf("test\r\n");

    while (1) {
        HAL_Delay(1000);
    }
}

/*********************************************END OF FILE**********************/
