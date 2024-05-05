/**
 ******************************************************************************
 * @file     main.c
 * @author   embedfire
 * @version  V1.0
 * @date     2024
 * @brief    OLED����
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
#include "main.h"
#include "led/bsp_gpio_led.h"
#include "usart/bsp_usart_debug.h"
#include "iic/bsp_iic_oled.h"

/**
 * @brief  ������
 * @param  ��
 * @note  	��
 * @retval ��
 */
int main(void)
{
    HAL_Init(); /* HAL���ʼ�� */

    Bsp_Led_Init(); /* LED ��ʼ�� */

    Bsp_IIC_Init();

    // OLED_Init(); // ��ʼ��OLED

    // OLED_Fill(0xFF); // ȫ������

    // unsigned char i;
    while (1) {
        // OLED_Fill(0xFF);//ȫ������
        // HAL_Delay(1000);		// 1s

        // OLED_Fill(0x00);//ȫ����
        // HAL_Delay(1000);		// 1s

        // for(i=0;i<4;i++)
        // {
        // 	OLED_ShowCN(22+i*16,0,i);									//������ʾ����
        // }

        // HAL_Delay(2000);		// 1s
        // OLED_ShowStr(0,3,(unsigned char*)"Wildfire Tech",1);				//����6*8�ַ�
        // OLED_ShowStr(0,4,(unsigned char*)"Hello wildfire",2);				//����8*16�ַ�
        // HAL_Delay(1000);
        // OLED_CLS();//����
        // OLED_OFF();//����OLED����
        // HAL_Delay(1000);		// 1s
        // OLED_ON();//����OLED���ߺ���
    }
}

/*********************************************END OF FILE**********************/
