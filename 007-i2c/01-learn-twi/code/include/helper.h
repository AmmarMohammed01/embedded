#ifndef __HELPER_H__
#define __HELPER_H__
#include <math.h>
#include <stdint.h>
void intToString(uint16_t num, char * output);
void reverseString(char * str);
float tmp1075_raw_to_celsius(uint16_t rawData);
float tmp1075_raw_to_fahrenheit(uint16_t rawData);
#endif
