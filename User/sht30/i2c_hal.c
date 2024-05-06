//=============================================================================
// S E N S I R I O N AG, Laubisruetistr. 50, CH-8712 Staefa, Switzerland
//=============================================================================
// Project : SHT3x Sample Code (V1.1)
// File : i2c_hal.c (V1.1)
// Author : RFU
// Date : 6-Mai-2015
// Controller: STM32F100RB
// IDE : ¦ÌVision V5.12.0.0
// Compiler : Armcc
// Brief : I2C hardware abstraction layer
//=============================================================================

//-- Includes -----------------------------------------------------------------
#include "i2c_hal.h"
//-- Defines ------------------------------------------------------------------
I2C_HandleTypeDef I2cHandle;
// I2C IO-Pins /* -- adapt the defines for your uC -- */
// SDA on port B, bit 14
// #define SDA_LOW()  (GPIOB->BSRR = 0x40000000) // set SDA to low
// #define SDA_OPEN() (GPIOB->BSRR = 0x00004000) // set SDA to open-drain
// #define SDA_READ   (GPIOB->IDR & 0x4000)      // read SDA
// // SCL on port B, bit 13 /* -- adapt the defines for your uC -- */
// #define SCL_LOW()  (GPIOB->BSRR = 0x20000000) // set SCL to low
// #define SCL_OPEN() (GPIOB->BSRR = 0x00002000) // set SCL to open-drain
// #define SCL_READ   (GPIOB->IDR & 0x2000)      // read SCL

//-- Static function prototypes -----------------------------------------------
static etError I2c_WaitWhileClockStreching(u8t timeout);

//-----------------------------------------------------------------------------
void I2c_Init(void) /* -- adapt the init for your uC -- */
{
    I2cHandle.Instance             = I2C;
    I2cHandle.Mode                 = HAL_I2C_MODE_MASTER;
    I2cHandle.Init.ClockSpeed      = 4000000;
    I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE_16_9;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&I2cHandle) != HAL_OK)
        Usart_SendString("Init Hal_IIC error!");
}

//-----------------------------------------------------------------------------
void I2c_StartCondition(void)
{
    // SDA_OPEN();
    // DelayMicroSeconds(1);
    // SCL_OPEN();
    // DelayMicroSeconds(1);
    // SDA_LOW();
    // DelayMicroSeconds(10); // hold time start condition (t_HD;STA)
    // SCL_LOW();
    // DelayMicroSeconds(10);
}

//-----------------------------------------------------------------------------
void I2c_StopCondition(void)
{
    // SCL_LOW();
    // DelayMicroSeconds(1);
    // SDA_LOW();
    // DelayMicroSeconds(1);
    // SCL_OPEN();
    // DelayMicroSeconds(10); // set-up time stop condition (t_SU;STO)
    // SDA_OPEN();
    // DelayMicroSeconds(10);
}

//-----------------------------------------------------------------------------
etError I2c_WriteByte(u8t txByte)
{
    // etError error = NO_ERROR;

        // u8t mask;
    // for (mask = 0x80; mask > 0; mask >>= 1) // shift bit for masking (8 times)
    // {
    //     if ((mask & txByte) == 0)
    //         SDA_LOW(); // masking txByte, write bit to SDA-Line
    //     else
    //         SDA_OPEN();
    //     DelayMicroSeconds(1); // data set-up time (t_SU;DAT)
    //     SCL_OPEN();           // generate clock pulse on SCL
    //     DelayMicroSeconds(5); // SCL high time (t_HIGH)
    //     SCL_LOW();
    //     DelayMicroSeconds(1); // data hold time(t_HD;DAT)
    // }
    // SDA_OPEN();                      // release SDA-line
    // SCL_OPEN();                      // clk #9 for ack
    // DelayMicroSeconds(1);            // data set-up time (t_SU;DAT)
    // if (SDA_READ) error = ACK_ERROR; // check ack from i2c slave
    // SCL_LOW();
    // DelayMicroSeconds(20); // wait to see byte package on scope

    // return error; // return error code
    return HAL_I2C_Master_Transmit(&I2cHandle, SHT30_Address, &txByte, 1, 100);
}

//-----------------------------------------------------------------------------
etError I2c_ReadByte(u8t *rxByte, etI2cAck ack, u8t timeout)
{
    // etError error = NO_ERROR;
    // u8t mask;
    // *rxByte = 0x00;
    // SDA_OPEN();                             // release SDA-line
    // for (mask = 0x80; mask > 0; mask >>= 1) // shift bit for masking (8 times)
    // {
    //     SCL_OPEN();                                   // start clock on SCL-line
    //     DelayMicroSeconds(1);                         // clock set-up time (t_SU;CLK)
    //     error = I2c_WaitWhileClockStreching(timeout); // wait while clock streching
    //     DelayMicroSeconds(3);                         // SCL high time (t_HIGH)
    //     if (SDA_READ) *rxByte |= mask;                // read bit
    //     SCL_LOW();
    //     DelayMicroSeconds(1); // data hold time(t_HD;DAT)
    // }
    // if (ack == ACK)
    //     SDA_LOW(); // send acknowledge if necessary
    // else
    //     SDA_OPEN();
    // DelayMicroSeconds(1); // data set-up time (t_SU;DAT)
    // SCL_OPEN();           // clk #9 for ack
    // DelayMicroSeconds(5); // SCL high time (t_HIGH)
    // SCL_LOW();
    // SDA_OPEN();            // release SDA-line
    // DelayMicroSeconds(20); // wait to see byte package on scope
    // return error;          // return with no error
    return HAL_I2C_Master_Receive(&I2cHandle, SHT30_Address, &rxByte, 1, 100);
}

//-----------------------------------------------------------------------------
etError I2c_GeneralCallReset(void)
{
    etError error;
    // I2c_StartCondition();
    // error = I2c_WriteByte(0x00);
    // if (error == NO_ERROR) error = I2c_WriteByte(0x06);
    return error;
}

//-----------------------------------------------------------------------------
static etError I2c_WaitWhileClockStreching(u8t timeout)
{
    etError error = NO_ERROR;
    // while (SCL_READ == 0) {
    //     if (timeout-- == 0) return TIMEOUT_ERROR;
    //     DelayMicroSeconds(1000);
    // }
    return error;
}
