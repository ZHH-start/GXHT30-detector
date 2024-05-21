#include "command_list.h"
#include "stdio.h"

uint8_t command;

void command_run()
{
    if (command == 1) {
        printf("temp=25,humi=70\r\n");
        command = 0;
    }
    if (command==2)
    {
        printf("temp=25,humi=70\r\n");
    }
    
}