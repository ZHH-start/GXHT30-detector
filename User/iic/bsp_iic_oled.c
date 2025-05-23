/**
 ******************************************************************************
 * @file     bsp_iic_oled.c
 * @author   embedfire
 * @version  V1.0
 * @date     2024
 * @brief    IIC OLED应用接口
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
#include "iic/bsp_iic_oled.h"
#include "iic/codetab.h"

I2C_HandleTypeDef I2cHandle;

/**
 * @brief  LED初始化
 * @param  无
 * @note  	无
 * @retval 无
 */
void Bsp_IIC_Init(void)
{
    I2cHandle.Instance             = I2C;
    I2cHandle.Mode                 = HAL_I2C_MODE_MASTER;
    I2cHandle.Init.ClockSpeed      = I2C_SPEEDCLOCK;
    I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE;
    I2cHandle.Init.OwnAddress1     = I2C_ADDRESS;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&I2cHandle);
}

/**
 * @brief  I2C_WriteByte，向OLED寄存器地址写一个byte的数据
 * @param  addr：寄存器地址
 *					data：要写入的数据
 * @retval 无
 */
void I2C_WriteByte(uint8_t addr, uint8_t data)
{
    HAL_I2C_Mem_Write(&I2cHandle, I2C_ADDRESS, addr, 1, &data, 1, 1000);
}

/**
 * @brief  WriteCmd，向OLED写入命令
 * @param  I2C_Command：命令代码
 * @retval 无
 */
void WriteCmd(unsigned char I2C_Command) // 写命令
{
    I2C_WriteByte(0x00, I2C_Command);
}

/**
 * @brief  WriteDat，向OLED写入数据
 * @param  I2C_Data：数据
 * @retval 无
 */
void WriteDat(unsigned char I2C_Data) // 写数据
{
    I2C_WriteByte(0x40, I2C_Data);
}

/**
 * @brief  OLED_Init，初始化OLED
 * @param  无
 * @retval 无
 */
void OLED_Init(void)
{
    HAL_Delay(1); // 1s,这里的延时很重要,上电后延时，没有错误的冗余设计

    WriteCmd(0xAE); // display off
    WriteCmd(0x20); // Set Memory Addressing Mode
    WriteCmd(0x10); // 00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    WriteCmd(0xb0); // Set Page Start Address for Page Addressing Mode,0-7
    WriteCmd(0xc8); // Set COM Output Scan Direction
    WriteCmd(0x00); //---set low column address
    WriteCmd(0x10); //---set high column address
    WriteCmd(0x40); //--set start line address
    WriteCmd(0x81); //--set contrast control register
    WriteCmd(0xff); // 亮度调节 0x00~0xff
    WriteCmd(0xa1); //--set segment re-map 0 to 127
    WriteCmd(0xa6); //--set normal display
    WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
    WriteCmd(0x3F); //
    WriteCmd(0xa4); // 0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    WriteCmd(0xd3); //-set display offset
    WriteCmd(0x00); //-not offset
    WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
    WriteCmd(0xf0); //--set divide ratio
    WriteCmd(0xd9); //--set pre-charge period
    WriteCmd(0x22); //
    WriteCmd(0xda); //--set com pins hardware configuration
    WriteCmd(0x12);
    WriteCmd(0xdb); //--set vcomh
    WriteCmd(0x20); // 0x20,0.77xVcc
    WriteCmd(0x8d); //--set DC-DC enable
    WriteCmd(0x14); //
    WriteCmd(0xaf); //--turn on oled panel
}

/**
 * @brief  OLED_SetPos，设置光标
 * @param  x,光标x位置
 *					y，光标y位置
 * @retval 无
 */
void OLED_SetPos(unsigned char x, unsigned char y) // 设置起始点坐标
{
    WriteCmd(0xb0 + y);
    WriteCmd(((x & 0xf0) >> 4) | 0x10);
    WriteCmd((x & 0x0f) | 0x01);
}

/**
 * @brief  OLED_Fill，填充整个屏幕
 * @param  fill_Data:要填充的数据
 * @retval 无
 */
void OLED_Fill(unsigned char fill_Data) // 全屏填充
{
    unsigned char m, n;
    for (m = 0; m < 8; m++) {
        WriteCmd(0xb0 + m); // page0-page1
        WriteCmd(0x00);     // low column start address
        WriteCmd(0x10);     // high column start address
        for (n = 0; n < 128; n++) {
            WriteDat(fill_Data);
        }
    }
}

/**
 * @brief  OLED_CLS，清屏
 * @param  无
 * @retval 无
 */
void OLED_CLS(void) // 清屏
{
    OLED_Fill(0x00);
}

/**
 * @brief  OLED_ON，将OLED从休眠中唤醒
 * @param  无
 * @retval 无
 */
void OLED_ON(void)
{
    WriteCmd(0X8D); // 设置电荷泵
    WriteCmd(0X14); // 开启电荷泵
    WriteCmd(0XAF); // OLED唤醒
}

/**
 * @brief  OLED_OFF，让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
 * @param  无
 * @retval 无
 */
void OLED_OFF(void)
{
    WriteCmd(0X8D); // 设置电荷泵
    WriteCmd(0X10); // 关闭电荷泵
    WriteCmd(0XAE); // OLED休眠
}

/**
 * @brief  OLED_ShowStr，显示codetab.h中的ASCII字符,有6*8和8*16可选择
 * @param  x,y : 起始点坐标(x:0~127, y:0~7);
 *					ch[] :- 要显示的字符串;
 *					TextSize : 字符大小(1:6*8 ; 2:8*16)
 * @retval 无
 */
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
    unsigned char c = 0, i = 0, j = 0;
    switch (TextSize) {
        case 1: {
            while (ch[j] != '\0') {
                c = ch[j] - 32;
                if (x > 126) {
                    x = 0;
                    y++;
                }
                OLED_SetPos(x, y);
                for (i = 0; i < 6; i++)
                    WriteDat(F6x8[c][i]);
                x += 6;
                j++;
            }
        } break;
        case 2: {
            while (ch[j] != '\0') {
                c = ch[j] - 32;
                if (x > 120) {
                    x = 0;
                    y++;
                }
                OLED_SetPos(x, y);
                for (i = 0; i < 8; i++)
                    WriteDat(F8X16[c * 16 + i]);
                OLED_SetPos(x, y + 1);
                for (i = 0; i < 8; i++)
                    WriteDat(F8X16[c * 16 + i + 8]);
                x += 8;
                j++;
            }
        } break;
    }
}

/**
 * @brief  OLED_ShowCN，显示codetab.h中的汉字,16*16点阵
 * @param  x,y: 起始点坐标(x:0~127, y:0~7);
 *					N:汉字在codetab.h中的索引
 * @retval 无
 */
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
    unsigned char wm   = 0;
    unsigned int adder = 32 * N;
    OLED_SetPos(x, y);
    for (wm = 0; wm < 16; wm++) {
        WriteDat(F16x16[adder]);
        adder += 1;
    }
    OLED_SetPos(x, y + 1);
    for (wm = 0; wm < 16; wm++) {
        WriteDat(F16x16[adder]);
        adder += 1;
    }
}

/**
 * @brief  OLED_DrawBMP，显示BMP位图
 * @param  x0,y0 :起始点坐标(x0:0~127, y0:0~7);
 *					x1,y1 : 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
 * @retval 无
 */
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[])
{
    unsigned int j = 0;
    unsigned char x, y;

    if (y1 % 8 == 0)
        y = y1 / 8;
    else
        y = y1 / 8 + 1;
    for (y = y0; y < y1; y++) {
        OLED_SetPos(x0, y);
        for (x = x0; x < x1; x++) {
            WriteDat(BMP[j++]);
        }
    }
}
