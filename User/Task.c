#include "Task.h"
#include "app.h"
#include "app_led.h"

//========================================================================
//                               本地变量声明
//========================================================================

static TASK_COMPONENTS Task_Comps[] = {
    // 状态  启动时间  周期  函数
    {0, 1, 250, app_led_toggle}, /* task 1 Period： 250ms */
    {0, 1, 10, app_sht_read},   /* task 2 Period： 500ms */
    {0, 1, 10, app_uart_control},

    {0, 10, 10, app_humi_send_once},
    {0, 10, 10000, app_humi_send_low_speed},
    {0, 10, 1000, app_humi_send_medium_speed},
    {0, 10, 100, app_humi_send_high_speed},

    {0, 10, 10, app_temp_send_once},
    {0, 10, 10000, app_temp_send_low_speed},
    {0, 10, 1000, app_temp_send_medium_speed},
    {0, 10, 100, app_temp_send_high_speed},

};

uint8_t Tasks_Max = sizeof(Task_Comps) / sizeof(Task_Comps[0]);

//========================================================================
// 函数: Task_Handler_Callback
// 描述: 任务标记回调函数.
// 参数: None.
// 返回: None.
// 版本: V1.0, 2012-10-22
//========================================================================
void Task_Marks_Handler_Callback(void)
{
    uint8_t i;
    for (i = 0; i < Tasks_Max; i++) {
        if (Task_Comps[i].TIMCount) /* If the time is not 0 */
        {
            Task_Comps[i].TIMCount--;        /* Time counter decrement */
            if (Task_Comps[i].TIMCount == 0) /* If time arrives */
            {
                /*Resume the timer value and try again */
                Task_Comps[i].TIMCount = Task_Comps[i].TRITime;
                Task_Comps[i].Run      = 1; /* The task can be run */
            }
        }
    }
}

//========================================================================
// 函数: Task_Pro_Handler_Callback
// 描述: 任务处理回调函数.
// 参数: None.
// 返回: None.
// 版本: V1.0, 2012-10-22
//========================================================================
void Task_Pro_Handler_Callback(void)
{
    uint8_t i;
    for (i = 0; i < Tasks_Max; i++) {
        if (Task_Comps[i].Run) /* If task can be run */
        {
            Task_Comps[i].Run = 0;    /* Flag clear 0 */
            Task_Comps[i].TaskHook(); /* Run task */
        }
        // printf("waiting");
    }
}
