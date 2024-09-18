#ifndef __APP_SHT_READ_H
#define __APP_SHT_READ_H

#include "main.h"
#include "app.h"

#define I2C_ADDRESS      0x78               /* Local address 0xA0 */
#define I2C_SPEEDCLOCK   4000             /* Communication speed 100K */
#define I2C_DUTYCYCLE    I2C_DUTYCYCLE_2 /* Duty cycle */

void app_sht_read_init();
void app_sht_read();

#endif
