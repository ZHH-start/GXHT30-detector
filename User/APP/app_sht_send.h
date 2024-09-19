#ifndef __APP_SHT_SEND_H
#define __APP_SHT_SEND_H

#include "main.h"
#include "app.h"

#define TEMP_SEND_OFF    0
#define TEMP_SEND_LOW_SPEED    1 //0.1s一次
#define TEMP_SEND_MEDIUM_SPEED 2//1s一次
#define TEMP_SEND_HIGH_SPEED   3//10s一次
#define TEMP_SEND_ONCE    4//只发送一次

#define HUMI_SEND_OFF    0
#define HUMI_SEND_LOW_SPEED    1
#define HUMI_SEND_MEDIUM_SPEED 2
#define HUMI_SEND_HIGH_SPEED   3
#define HUMI_SEND_ONCE    4

void app_temp_send_low_speed();
void app_temp_send_medium_speed();
void app_temp_send_high_speed();
void app_temp_send_once();

void app_humi_send_low_speed();
void app_humi_send_medium_speed();
void app_humi_send_high_speed();
void app_humi_send_once();

#endif
