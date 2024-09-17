#include "app_sht_read.h"

#include "sensirion_common.h"
#include "sensirion_i2c_hal.h"
#include "sht3x_i2c.h"

int32_t temperature = 0;
int32_t humidity    = 0;

I2C_HandleTypeDef I2cHandle;

void app_sht_read_init()
{
    I2cHandle.Instance             = I2C;
    I2cHandle.Mode                 = HAL_I2C_MODE_MASTER;
    I2cHandle.Init.ClockSpeed      = I2C_SPEEDCLOCK;
    I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE;
    I2cHandle.Init.OwnAddress1     = I2C_ADDRESS;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&I2cHandle);
    
    sensirion_i2c_hal_init();
    sht3x_init(SHT30_I2C_ADDR_44);
}

void app_sht_read()
{
    sht3x_measure_single_shot(REPEATABILITY_MEDIUM, false, &temperature, &humidity);
    printf("temp:%d\r\nhumi:%d\r\n", temperature, humidity);
}