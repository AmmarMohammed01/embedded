#ifndef __I2C_H__
#define __I2C_H__

#include <avr/io.h>
#include <stdint.h>

#define TMP1075_ADDR 0x48

void i2c_init();
uint16_t i2c_read_twobytes();
#endif
