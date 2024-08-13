#ifndef __COMMAND_LIST_H
#define __COMMAND_LIST_H

/* ��������ͷ�ļ� */
#include "py32f0xx_hal.h"

#define COMMAND_1 "CM+read\r\n"
// #define COMMAND_2 "CM+fastread\r\n"
#define COMMAND_3 "CM+isr_read=1s\r\n" // һ��ش�һ�� ָ��
#define COMMAND_4 "CM+isr_read=2s\r\n" // ����ش�һ�� ָ��
#define COMMAND_5 "CM+stop_isr\r\n"

#define COMMAND_6 "CM+baud_rate=9600\r\n"
#define COMMAND_7 "CM+baud_rate=115200\r\n"
// #define COMMAND_9 "CM+baud_rate=921600\r\n"

extern uint8_t command;

void command_run();

#endif /* __BSP_EXIT_KEY_H */
