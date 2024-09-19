#ifndef __APP_H_
#define __APP_H_

//========================================================================
//                                ͷ�ļ�
//========================================================================

#include "app_led.h"
#include "app_sht_read.h"
#include "app_sht_send.h"
#include "app_uart_control.h"

//========================================================================
//                               ���غ����ͱ�������
//========================================================================
void sys_init();
//========================================================================
//                            �ⲿ�����ͱ�������
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

extern int32_t temperature; // �¶�
extern int32_t humidity;    // ʪ��

extern uint8_t temp_send_speed;
extern uint8_t humi_send_speed;

extern int uart_control; // ���ڲ����ʿ���

#endif
