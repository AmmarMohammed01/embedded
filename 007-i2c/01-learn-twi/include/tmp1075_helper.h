#ifndef __TMP1075_HELPER_H__
#define __TMP1075_HELPER_H__
#include <stdint.h>
#include "helper.h"
#include "usart.h"

typedef struct TMP1075_Info {
	uint8_t sign;
	uint8_t wholeNum;
	uint16_t fractionNum;
} tmp1075_info_t;

tmp1075_info_t tmp1075_raw_divide(uint16_t rawData);
void printTemperature(tmp1075_info_t info);

#endif
