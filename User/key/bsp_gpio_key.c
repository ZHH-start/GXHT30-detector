/**
  ******************************************************************************
  * @file     bsp_gpio_key.c
  * @author   embedfire
  * @version  V1.0
  * @date     2024
  * @brief    ����Ӧ��bsp��ɨ��ģʽ��
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
#include "key/bsp_gpio_key.h"


/**
  * @brief  KEY��ʼ��
  * @param  ��
  * @note  	��
  * @retval ��
  */
void Bsp_Key_Init(void)
{
    GPIO_InitTypeDef	GPIO_Key_InitConfig;
    
    /* Key GPIOʱ��ʹ�� */
    Key1_GPIO_CLK_ENABLE();                          
    Key2_GPIO_CLK_ENABLE(); 
    
    GPIO_Key_InitConfig.Mode = GPIO_MODE_INPUT;
    GPIO_Key_InitConfig.Pull = GPIO_PULLUP;
    GPIO_Key_InitConfig.Speed = GPIO_SPEED_FREQ_HIGH;
    /* Key GPIO ��ʼ�� */
    GPIO_Key_InitConfig.Pin = Key1_GPIO_PIN;
    HAL_GPIO_Init(Key1_GPIO_PORT, &GPIO_Key_InitConfig);
    /* Key GPIO ��ʼ�� */
    GPIO_Key_InitConfig.Pin = Key2_GPIO_PIN;
    HAL_GPIO_Init(Key2_GPIO_PORT, &GPIO_Key_InitConfig);
}



/**
  * @brief  KEYɨ�躯��
  * @param  mode���Ƿ�֧������	1��֧��	0����֧��
  * @note  	��
  * @retval ���ذ���ֵ
  */
uint8_t Key_Scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* �������ɿ���־ */
    uint8_t keyval = 0;

    if (mode) key_up = 1;       /* ֧������ */

    if (key_up && (HAL_GPIO_ReadPin(Key1_GPIO_PORT, Key1_GPIO_PIN) == Dowm))  /* �����ɿ���־Ϊ1, ��������һ������������ */
    {          
                //HAL_Delay(10);/* ȥ���� */
        key_up = 0;
        while (HAL_GPIO_ReadPin(Key1_GPIO_PORT, Key1_GPIO_PIN) == Dowm)  
                    keyval |= (0x1<<0);
    }
    else if (HAL_GPIO_ReadPin(Key1_GPIO_PORT, Key1_GPIO_PIN) == UP)         /* û���κΰ�������, ��ǰ����ɿ� */
    {
        key_up = 1;
    }
        
        if (key_up && (HAL_GPIO_ReadPin(Key2_GPIO_PORT, Key2_GPIO_PIN) == Dowm))  /* �����ɿ���־Ϊ1, ��������һ������������ */
    {          
                //HAL_Delay(10);/* ȥ���� */
        key_up = 0;
        while (HAL_GPIO_ReadPin(Key2_GPIO_PORT, Key2_GPIO_PIN) == Dowm)  
                    keyval |= (0x1<<1);
    }
    else if (HAL_GPIO_ReadPin(Key2_GPIO_PORT, Key2_GPIO_PIN) == UP)         /* û���κΰ�������, ��ǰ����ɿ� */
    {
        key_up = 1;
    }

    return keyval;              /* ���ؼ�ֵ */
}

