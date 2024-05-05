#ifndef __BSP_IIC_OLED_H
#define __BSP_IIC_OLED_H

/* 包含其他头文件 */
#include "py32f0xx_hal.h"

 
/* 宏定义 */
#define I2C_ADDRESS      0x78               /* Local address 0xA0 */
#define I2C_SPEEDCLOCK   400000             /* Communication speed 100K */
#define I2C_DUTYCYCLE    I2C_DUTYCYCLE_16_9 /* Duty cycle */



/* 全局变量声明 */


/* 函数声明 */
void Bsp_IIC_Init(void);

void OLED_Init(void);

void OLED_Fill(unsigned char fill_Data);//全屏填充
    
void OLED_CLS(void);//清屏

void OLED_ON(void);

void OLED_OFF(void);

void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);

void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);

void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);



#endif /* __BSP_IIC_OLED_H */

