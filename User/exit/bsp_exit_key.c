/**
 ******************************************************************************
 * @file     bsp_gpio_key.c
 * @author   embedfire
 * @version  V1.0
 * @date     2024
 * @brief    ����Ӧ��bsp���ж�ģʽ��
 ******************************************************************************
 * @attention
 *
 * ʵ��ƽ̨��Ұ�� ebf_py32f002b PY32������
 * ��̳      ��http://www.firebbs.cn
 * ����      ��https://embedfire.com/
 * �Ա�      ��https://yehuosm.tmall.com/
 *
 ******************************************************************************
 */
#include "exit/bsp_exit_key.h"

EXTI_HandleTypeDef key1_exti_handle;
EXTI_HandleTypeDef key2_exti_handle;

/**
 * @brief  KEY��ʼ��
 * @param  ��
 * @note  	��
 * @retval ��
 */
void Bsp_EXIT_Init(void)
{
    GPIO_InitTypeDef GPIO_Key_InitConfig;
    EXTI_ConfigTypeDef EXTI_Key_InitConfig;
    /* Key GPIOʱ��ʹ�� */
    Key1_GPIO_CLK_ENABLE();
    Key2_GPIO_CLK_ENABLE();

    key1_exti_handle.Line            = EXTI_LINE_0;                  /* �����ⲿ�ж��� */
    key1_exti_handle.PendingCallback = Key1_Callback;                /* ע���ⲿ�ж��߹���ص����� */
    EXTI_Key_InitConfig.GPIOSel      = EXTI_GPIOA;                   /* GPIO �ⲿ�ж϶˿�ѡ�� */
    EXTI_Key_InitConfig.Line         = EXTI_LINE_0;                  /* �����ⲿ�ж��� */
    EXTI_Key_InitConfig.Mode         = EXTI_MODE_INTERRUPT;          /* �����ں˴����ⲿ�жϵ�ģʽ���ж�/�¼�/�ޣ� */
    EXTI_Key_InitConfig.Trigger      = EXTI_TRIGGER_FALLING;         /* �����ⲿ�жϴ������� */
    HAL_EXTI_SetConfigLine(&key1_exti_handle, &EXTI_Key_InitConfig); /* ����ָ���� EXTI ��· */
    HAL_NVIC_SetPriority(Key1_IRQ, 1, 0);                            /* �����ж����ȼ� */
    HAL_NVIC_EnableIRQ(Key1_IRQ);                                    /* ��ʼ��EXIT�ж� */

    key2_exti_handle.Line            = EXTI_LINE_3;                  /* �����ⲿ�ж��� */
    key2_exti_handle.PendingCallback = Key2_Callback;                /* ע���ⲿ�ж��߹���ص����� */
    EXTI_Key_InitConfig.GPIOSel      = EXTI_GPIOA;                   /* GPIO �ⲿ�ж϶˿�ѡ�� */
    EXTI_Key_InitConfig.Line         = EXTI_LINE_3;                  /* �����ⲿ�ж��� */
    EXTI_Key_InitConfig.Mode         = EXTI_MODE_INTERRUPT;          /* �����ں˴����ⲿ�жϵ�ģʽ���ж�/�¼�/�ޣ� */
    EXTI_Key_InitConfig.Trigger      = EXTI_TRIGGER_FALLING;         /* �����ⲿ�жϴ������� */
    HAL_EXTI_SetConfigLine(&key2_exti_handle, &EXTI_Key_InitConfig); /* ����ָ���� EXTI ��· */
    HAL_NVIC_SetPriority(Key2_IRQ, 1, 0);                            /* �����ж����ȼ� */
    HAL_NVIC_EnableIRQ(Key2_IRQ);                                    /* ��ʼ��EXIT�ж� */

    GPIO_Key_InitConfig.Mode  = GPIO_MODE_INPUT;
    GPIO_Key_InitConfig.Pull  = GPIO_PULLUP;
    GPIO_Key_InitConfig.Speed = GPIO_SPEED_FREQ_LOW;

    GPIO_Key_InitConfig.Pin = Key1_GPIO_PIN;
    HAL_GPIO_Init(Key1_GPIO_PORT, &GPIO_Key_InitConfig);    /* Key GPIO ��ʼ�� */

    GPIO_Key_InitConfig.Pin = Key2_GPIO_PIN;
    HAL_GPIO_Init(Key2_GPIO_PORT, &GPIO_Key_InitConfig);    /* Key GPIO ��ʼ�� */
}

/**
 * @brief  KEY1�жϻص�����
 * @param  ��
 * @note  	��
 * @retval ��
 */
void Key1_Callback(void)
{
    LED2_TOGGLE();
}

/**
 * @brief  KEY2�жϻص�����
 * @param  ��
 * @note  	��
 * @retval ��
 */
void Key2_Callback(void)
{
    LED3_TOGGLE();
}
