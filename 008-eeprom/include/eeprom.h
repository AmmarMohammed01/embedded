#ifndef __EEPROM_H__
#define __EEPROM_H__

#include <avr/io.h>

void eeprom_init();
void eeprom_write(unsigned int uiAddress, unsigned char ucData);
unsigned char eeprom_read(unsigned int uiAddress);

#endif
