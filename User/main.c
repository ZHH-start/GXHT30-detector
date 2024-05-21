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

    int16_t error = NO_ERROR;
    Bsp_Led_Init();                 /* LED ��ʼ�� */
    DEBUG_USART_Config(115200);     // UART��ʼ�� A6-TX A7-RX
    Rx_Data_Buf_Init(&Rx_Data_Buf); /* USART �������ݻ�������ʼ�� */

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
        //     Rx_Data_Buf.Is_Reseive_Use_Done = 0; // ��־λ��
        //     Rx_Data_Buf.Index               = 0; // �������
        //     memset(Rx_Data_Buf.data, 0, Rx_Data_Buf_Size); // ��ս��ջ�����
        // }
        command_run();
        HAL_Delay(100);
    }
}

/*********************************************END OF FILE**********************/
