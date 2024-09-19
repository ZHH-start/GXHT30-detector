#ifndef __APP_H_
#define __APP_H_

//========================================================================
//                                头文件
//========================================================================

#include "app_led.h"
#include "app_sht_read.h"
#include "app_sht_send.h"
#include "app_uart_control.h"

//========================================================================
//                               本地函数和变量声明
//========================================================================
void sys_init();
//========================================================================
//                            外部函数和变量声明
//========================================================================
#define COMMAND_UART_LOW "CM+BAUD=9600\r\n"
#define COMMAND_UART_HIGH "CM+BAUD=115200\r\n"

#define COMMAND_SEND_TEMP_ONCE "CM+TEMP_READ\r\n"
#define COMMAND_SEND_TEMP_LOWSPEED "CM+TEMP_READ=10s\r\n"
#define COMMAND_SEND_TEMP_MEDIUMSPEED "CM+TEMP_READ=1s\r\n"
#define COMMAND_SEND_TEMP_HIGHSPEED "CM+TEMP_READ=0.1s\r\n"
#define COMMAND_SEND_TEMP_OFF "CM+TEMP_READ=0s\r\n"

#define COMMAND_SEND_HUMI_ONCE "CM+HUMI_READ\r\n"
#define COMMAND_SEND_HUMI_LOWSPEED "CM+HUMI_READ=10s\r\n"
#define COMMAND_SEND_HUMI_MEDIUMSPEED "CM+HUMI_READ=1s\r\n"
#define COMMAND_SEND_HUMI_HIGHSPEED "CM+HUMI_READ=0.1s\r\n"
#define COMMAND_SEND_HUMI_OFF "CM+HUMI_READ=0s\r\n"

extern int32_t temperature; // 温度
extern int32_t humidity;    // 湿度

extern uint8_t temp_send_speed;
extern uint8_t humi_send_speed;

extern int uart_control; // 串口波特率控制

#endif
