#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <avr/io.h>
#include <stdint.h>

void button_init();
uint8_t button_read();

#endif
