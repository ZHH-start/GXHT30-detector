/**
  ******************************************************************************
  * @file     bsp_gpio_key.c
  * @author   embedfire
  * @version  V1.0
  * @date     2024
  * @brief    按键应用bsp（扫描模式）
  ******************************************************************************
  * @attention
  *
  * 实验平台：野火 ebf_py32f002b PY32开发板 
  * 论坛      ：http://www.firebbs.cn
  * 官网      ：https://embedfire.com/
  * 淘宝      ：https://yehuosm.tmall.com/
  *
  ******************************************************************************
  */
#include "key/bsp_gpio_key.h"


/**
  * @brief  KEY初始化
  * @param  无
  * @note  	无
  * @retval 无
  */
void Bsp_Key_Init(void)
{
    GPIO_InitTypeDef	GPIO_Key_InitConfig;
    
    /* Key GPIO时钟使能 */
    Key1_GPIO_CLK_ENABLE();                          
    Key2_GPIO_CLK_ENABLE(); 
    
    GPIO_Key_InitConfig.Mode = GPIO_MODE_INPUT;
    GPIO_Key_InitConfig.Pull = GPIO_PULLUP;
    GPIO_Key_InitConfig.Speed = GPIO_SPEED_FREQ_HIGH;
    /* Key GPIO 初始化 */
    GPIO_Key_InitConfig.Pin = Key1_GPIO_PIN;
    HAL_GPIO_Init(Key1_GPIO_PORT, &GPIO_Key_InitConfig);
    /* Key GPIO 初始化 */
    GPIO_Key_InitConfig.Pin = Key2_GPIO_PIN;
    HAL_GPIO_Init(Key2_GPIO_PORT, &GPIO_Key_InitConfig);
}



/**
  * @brief  KEY扫描函数
  * @param  mode：是否支持连按	1：支持	0：不支持
  * @note  	无
  * @retval 返回按键值
  */
uint8_t Key_Scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* 按键按松开标志 */
    uint8_t keyval = 0;

    if (mode) key_up = 1;       /* 支持连按 */

    if (key_up && (HAL_GPIO_ReadPin(Key1_GPIO_PORT, Key1_GPIO_PIN) == Dowm))  /* 按键松开标志为1, 且有任意一个按键按下了 */
    {          
                //HAL_Delay(10);/* 去抖动 */
        key_up = 0;
        while (HAL_GPIO_ReadPin(Key1_GPIO_PORT, Key1_GPIO_PIN) == Dowm)  
                    keyval |= (0x1<<0);
    }
    else if (HAL_GPIO_ReadPin(Key1_GPIO_PORT, Key1_GPIO_PIN) == UP)         /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }
        
        if (key_up && (HAL_GPIO_ReadPin(Key2_GPIO_PORT, Key2_GPIO_PIN) == Dowm))  /* 按键松开标志为1, 且有任意一个按键按下了 */
    {          
                //HAL_Delay(10);/* 去抖动 */
        key_up = 0;
        while (HAL_GPIO_ReadPin(Key2_GPIO_PORT, Key2_GPIO_PIN) == Dowm)  
                    keyval |= (0x1<<1);
    }
    else if (HAL_GPIO_ReadPin(Key2_GPIO_PORT, Key2_GPIO_PIN) == UP)         /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }

    return keyval;              /* 返回键值 */
}

