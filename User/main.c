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

    // sht3x_stop_measurement();
    // HAL_Delay(1);
    // sht3x_soft_reset();
    // HAL_Delay(100);
    // uint16_t a_status_register = 0u;

    // error = sht3x_read_status_register(&a_status_register);
    // if (error != NO_ERROR) {
    //     printf("error executing read_status_register(): %i\n", error);
    //     return error;
    // }
    // printf("a_status_register: %02x\n", a_status_register);

    int32_t a_temperature = 0;
    int32_t a_humidity    = 0;

    uint16_t raw_temp;
    uint16_t raw_humi;

    // uint16_t repetition   = 0;
    error = sht3x_start_periodic_measurement(REPEATABILITY_MEDIUM, MPS_ONE_PER_SECOND);

    while (1) {
        sht3x_read_measurement(&raw_temp, &raw_humi);
        a_temperature = signal_temperature(raw_temp);
        a_humidity    = signal_humidity(raw_humi);
        printf("a_temperature  [milli degC]: %i ", a_temperature);
        printf("a_humidity  [milli RH]: %i\n", a_humidity);

        // error = sht3x_measure_single_shot(REPEATABILITY_MEDIUM, false, &a_temperature, &a_humidity);
        // error = sht3x_blocking_read_measurement(&a_temperature, &a_humidity);
        // if (error != NO_ERROR) {
        //     printf("error executing measure_single_shot(): %i\n", error);
        //     continue;
        // }
        // printf("a_temperature  [milli degC]: %i ", a_temperature);
        // printf("a_humidity  [milli RH]: %i\n", a_humidity);
        // error = sht3x_stop_measurement();
        HAL_Delay(1000);

        sht3x_read_measurement(&raw_temp, &raw_humi);
        a_temperature = signal_temperature(raw_temp);
        a_humidity    = signal_humidity(raw_humi);
        printf("a_temperature  [milli degC]: %i ", a_temperature);
        printf("a_humidity  [milli RH]: %i\n", a_humidity);
        HAL_Delay(1500);

        sht3x_read_measurement(&raw_temp, &raw_humi);
        a_temperature = signal_temperature(raw_temp);
        a_humidity    = signal_humidity(raw_humi);
        printf("a_temperature  [milli degC]: %i ", a_temperature);
        printf("a_humidity  [milli RH]: %i\n", a_humidity);
        HAL_Delay(3000);
    }
}

/*********************************************END OF FILE**********************/
