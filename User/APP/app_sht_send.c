#include "app_sht_send.h"

uint8_t temp_send_speed = 0;
uint8_t humi_send_speed = 0;

void app_temp_send_once()
{
    if (temp_send_speed == TEMP_SEND_ONCE) {
        printf("temperature:%d\r\n", temperature);
        temp_send_speed = TEMP_SEND_OFF;
    }
}

void app_temp_send_low_speed()
{
    if (temp_send_speed == TEMP_SEND_LOW_SPEED) {
        printf("temperature high:%d\r\n", temperature);
    }
}

void app_temp_send_medium_speed()
{
    if (temp_send_speed == TEMP_SEND_MEDIUM_SPEED) {
        printf("temperature:%d\r\n", temperature);
    }
}

void app_temp_send_high_speed()
{
    if (temp_send_speed == TEMP_SEND_HIGH_SPEED) {
        printf("temperature:%d\r\n", temperature);
    }
}

void app_humi_send_once()
{
    if (humi_send_speed == HUMI_SEND_ONCE) {
        printf("humidity:%d\r\n", humidity);
        humi_send_speed = HUMI_SEND_OFF;
    }
}

void app_humi_send_low_speed()
{
    if (humi_send_speed == HUMI_SEND_LOW_SPEED) {
        printf("humidity:%d\r\n", humidity);
    }
}

void app_humi_send_medium_speed()
{
    if (humi_send_speed == HUMI_SEND_MEDIUM_SPEED) {
        printf("humidity:%d\r\n", humidity);
    }
}

void app_humi_send_high_speed()
{
    if (humi_send_speed == HUMI_SEND_HIGH_SPEED) {
        printf("humidity:%d\r\n", humidity);
    }
}