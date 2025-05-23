/*
 * Copyright (c) 2018, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "py32f0xx_hal.h"

#include "sensirion_common.h"
#include "sensirion_config.h"
#include "sensirion_i2c_hal.h"

/**
 * Create new I2C instance. You may also use a different interface, e.g. hi2c2,
 * depending on your CubeMX configuration
 */
static I2C_HandleTypeDef I2cHandle;

/**
 * Initialize all hard- and software components that are needed for the I2C communication.
 * 初始化相关硬件
 */
void sensirion_i2c_hal_init(void)
{
    I2cHandle.Instance             = I2C;
    I2cHandle.Init.ClockSpeed      = 100000;
    I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE_2;
    I2cHandle.Init.OwnAddress1     = 0;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&I2cHandle);
}

/**
 * Release all resources initialized by sensirion_i2c_hal_init().
 */
void sensirion_i2c_hal_free(void)
{
}

/**
 * Execute one read transaction on the I2C bus, reading a given number of bytes.
 * If the device does not acknowledge the read command, an error shall be
 * returned.
 * i2c连续读（接收），如果设备无应答，将产生一个错误。
 *
 * @param address 7-bit I2C address to read from
 * @param data    pointer to the buffer where the data is to be stored
 * @param count   number of bytes to read from I2C and store in the buffer
 * @returns 0 on success, error code otherwise
 */
int8_t sensirion_i2c_hal_read(uint8_t address, uint8_t *data, uint8_t count)
{
    return (int8_t)HAL_I2C_Master_Receive(&I2cHandle, (uint16_t)(address << 1),
                                          data, count, 100);
}

/**
 * Execute one write transaction on the I2C bus, sending a given number of
 * bytes. The bytes in the supplied buffer must be sent to the given address. If
 * the slave device does not acknowledge any of the bytes, an error shall be
 * returned.
 * i2c连续写（发送），如果设备无应答，将产生一个错误。
 *
 * @param address 7-bit I2C address to write to
 * @param data    pointer to the buffer containing the data to write
 * @param count   number of bytes to read from the buffer and send over I2C
 * @returns 0 on success, error code otherwise
 */
int8_t sensirion_i2c_hal_write(uint8_t address, const uint8_t *data, uint8_t count)
{
    return (int8_t)HAL_I2C_Master_Transmit(&I2cHandle, (uint16_t)(address << 1),
                                           (uint8_t *)data, count, 100);
}

/**
 * Sleep for a given number of microseconds. The function should delay the
 * execution for at least the given time, but may also sleep longer.
 * 微秒等待（不精确）
 *
 * @param useconds 等待的微秒值
 */
void sensirion_i2c_hal_sleep_usec(uint32_t useconds)
{
    uint32_t msec = useconds / 1000;
    if (useconds % 1000 > 0) {
        msec++;
    }

    /*
     * Increment by 1 if STM32F1 driver version less than 1.1.1 如果HAL库版本过低则进行相关处理。PY32版本很高，不需要。
     * Old firmwares of STM32F1 sleep 1ms shorter than specified in HAL_Delay.
     * This was fixed with firmware 1.6 (driver version 1.1.1), so we have to
     * fix it ourselves for older firmwares
     */
    // if (HAL_GetHalVersion() < 0x01010100) {
    //     msec++;
    // }

    HAL_Delay(msec);
}
