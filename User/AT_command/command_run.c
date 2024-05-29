#include "command_list.h"
#include "sht3x_i2c.h"
#include "sensirion_common.h"
#include "stdio.h"

uint8_t command, internal_command=0;

int32_t temperature = 0;
int32_t humidity    = 0;
uint16_t internal_temp;
uint16_t internal_humi;

void command_run()
{
    // int16_t error       = NO_ERROR;

    switch (command) {
        case 1: {
            sht3x_measure_single_shot(REPEATABILITY_MEDIUM, false, &temperature, &humidity);
            printf("temp:%d\r\nhumi:%d\r\n", temperature, humidity);
            command = 0;
        } break;
        case 2: {

        } break;
        case 3: {
            sht3x_start_periodic_measurement(REPEATABILITY_MEDIUM, MPS_ONE_PER_SECOND); // �����ж϶�ȡ��ʪ��-1sһ��
            internal_command = 1;                                                       // �����ڲ�ָ��1
            command          = 0;                                                       // ��caseִֻ��һ��
        } break;

        case 4: {
            sht3x_start_periodic_measurement(REPEATABILITY_MEDIUM, MPS_TWO_PER_SECOND); // �����ж϶�ȡ��ʪ��-2sһ��
            internal_command = 2;                                                       // �����ڲ�ָ��2
            command          = 0;                                                       // ��caseִֻ��һ��
        } break;

        case 5: {
            sht3x_stop_measurement();
            internal_command = 0;
            command          = 0;
        } break;

        default:
            break;
    }
    switch (internal_command) {
        case 1: {
            HAL_Delay(1000);
            sht3x_read_measurement(&internal_temp, &internal_humi); // ��ȡ����
            temperature = signal_temperature(internal_temp);        // �����¶�����
            humidity    = signal_humidity(internal_humi);           // ����ʪ������
            printf("temp:%d\r\nhumi:%d\r\n", temperature, humidity);
        } break;

        case 2: {
            HAL_Delay(2000);
            sht3x_read_measurement(&internal_temp, &internal_humi); // ��ȡ����
            temperature = signal_temperature(internal_temp);        // �����¶�����
            humidity    = signal_humidity(internal_humi);           // ����ʪ������
            printf("temp:%d\r\nhumi:%d\r\n", temperature, humidity);
        } break;

        default:
            break;
    }
}