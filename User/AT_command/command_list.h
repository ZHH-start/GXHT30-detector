#ifndef __COMMAND_LIST_H
#define __COMMAND_LIST_H

/* ��������ͷ�ļ� */
#include "py32f0xx_hal.h"

#define COMMAND_1 "AT+read\r\n"
#define COMMAND_2 "AT+fastread\r\n"
#define COMMAND_3 "AT+isr_read=1s\r\n" // һ��ش�һ�� ָ��
#define COMMAND_4 "AT+isr_read=2s\r\n" // ����ش�һ�� ָ��
#define COMMAND_5 "AT+stop_isr\r\n"
// #define COMMAND_6 "1234567"
// #define COMMAND_7 "1234567"
// #define COMMAND_8 "1234567"
// #define COMMAND_9 "1234567"

extern uint8_t command;

void command_run();

#endif /* __BSP_EXIT_KEY_H */
