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

    Bsp_Led_Init();                 /* LED ��ʼ�� */
    DEBUG_USART_Config(115200);       // UART��ʼ�� A6-TX A7-RX
    Rx_Data_Buf_Init(&Rx_Data_Buf); /* USART �������ݻ�������ʼ�� */

    PWM_LED(LED_ON);

    sensirion_i2c_hal_init();
    sht3x_init(SHT30_I2C_ADDR_44);

    printf("MPT-SHT30-WIRE01 Init done\r\n");

    while (1) {
        command_run();
    }
}

/*********************************************END OF FILE**********************/
