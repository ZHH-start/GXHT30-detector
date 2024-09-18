#include "Task.h"
#include "app.h"
#include "app_led.h"

//========================================================================
//                               ���ر�������
//========================================================================

static TASK_COMPONENTS Task_Comps[] = {
    // ״̬  ����  ����  ����
    {0, 1, 250, app_led_toggle}, /* task 1 Period�� 250ms */
    {0, 1, 250, app_sht_read},   /* task 2 Period�� 500ms */
                                 //	{0, 20, 20, Sample_INTtoUART},		/* task 3 Period�� 20ms */

    /* Add new task here */
};

uint8_t Tasks_Max = sizeof(Task_Comps) / sizeof(Task_Comps[0]);

//========================================================================
// ����: Task_Handler_Callback
// ����: �����ǻص�����.
// ����: None.
// ����: None.
// �汾: V1.0, 2012-10-22
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
// ����: Task_Pro_Handler_Callback
// ����: ������ص�����.
// ����: None.
// ����: None.
// �汾: V1.0, 2012-10-22
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
