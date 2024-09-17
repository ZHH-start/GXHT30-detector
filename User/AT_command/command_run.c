#include "command_list.h"
#include "sht3x_i2c.h"
#include "sensirion_common.h"
#include "stdio.h"

// #include "bsp_gpio_led.h"
#include "bsp_usart_debug.h"

uint8_t command, internal_command = 0;

int32_t temperature = 0;
int32_t humidity    = 0;
uint16_t internal_temp;
uint16_t internal_humi;

uint16_t count = 0;

void command_run()
{
    HAL_Delay(1);

    switch (command) {
        case 1: {
            PWM_LED(LED_OFF);

            sht3x_measure_single_shot(REPEATABILITY_MEDIUM, false, &temperature, &humidity);
            printf("temp:%d\r\nhumi:%d\r\n", temperature, humidity);
            internal_command = 0;
            command          = 0;

            PWM_LED(LED_ON);
        } break;
        case 2: {

        } break;
        case 3: {
            PWM_LED(LED_OFF);

            sht3x_start_periodic_measurement(REPEATABILITY_MEDIUM, MPS_ONE_PER_SECOND); // 启动中断读取温湿度-1s一次
            internal_command = 1;                                                       // 启动内部指令1
            command          = 0;                                                       // 该case只执行一次

            // PWM_LED(LED_ON);
        } break;

        case 4: {
            PWM_LED(LED_OFF);

            sht3x_start_periodic_measurement(REPEATABILITY_MEDIUM, MPS_TWO_PER_SECOND); // 启动中断读取温湿度-2s一次
            internal_command = 2;                                                       // 启动内部指令2
            command          = 0;                                                       // 该case只执行一次

            // PWM_LED(LED_ON);
        } break;

        case 5: {
            sht3x_stop_measurement();
            internal_command = 0;
            command          = 0;
        } break;

        case 6: {
            DEBUG_USART_Config(9600);       // UART初始化 A6-TX A7-RX
            internal_command = 0;
            command          = 0;
        } break;

        case 7: {
            DEBUG_USART_Config(115200);       // UART初始化 A6-TX A7-RX
            internal_command = 0;
            command          = 0;
        } break;


        default:
            break;
    }
    switch (internal_command) {
        case 1: {
            if (count >= 500) {
                PWM_LED(LED_ON);

                count = 0;
                sht3x_read_measurement(&internal_temp, &internal_humi); // 读取出来
                temperature = signal_temperature(internal_temp);        // 处理温度数据
                humidity    = signal_humidity(internal_humi);           // 处理湿度数据
                printf("SHT30-temp:%d\r\nSHT30-humi:%d\r\n", temperature, humidity);
            } else
                count++;
        } break;

        case 2: {
            if (count >= 1000) {
                PWM_LED(LED_ON);
                
                count = 0;
                sht3x_read_measurement(&internal_temp, &internal_humi); // 读取出来
                temperature = signal_temperature(internal_temp);        // 处理温度数据
                humidity    = signal_humidity(internal_humi);           // 处理湿度数据
                printf("SHT30-temp:%d\r\nSHT30-humi:%d\r\n", temperature, humidity);
            } else
                count++;
        } break;

        default:
            count = 0;
            break;
    }
}