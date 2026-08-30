// 8/30/2026

#include <stdio.h>
#include <stdint.h>
#include "helper.h"

typedef struct TMP1075_Info {
	uint8_t sign;
	uint8_t wholeNum;
	uint16_t fractionNum;
} tmp1075_info_t;

//float tmp1075_raw_to_celsius(uint16_t rawData);
tmp1075_info_t tmp1075_raw_divide(uint16_t rawData);
void printTemperature(tmp1075_info_t info);

int main() {
	tmp1075_info_t rinfoMain = tmp1075_raw_divide(0x7FF0);
	printTemperature(rinfoMain);

	rinfoMain = tmp1075_raw_divide(0x8000);
	printTemperature(rinfoMain);

	rinfoMain = tmp1075_raw_divide(0x0010);
	printTemperature(rinfoMain);

	rinfoMain = tmp1075_raw_divide(0x0020);
	printTemperature(rinfoMain);

	rinfoMain = tmp1075_raw_divide(0x0040);
	printTemperature(rinfoMain);

	rinfoMain = tmp1075_raw_divide(0x0080);
	printTemperature(rinfoMain);

	rinfoMain = tmp1075_raw_divide(0x0000);
	printTemperature(rinfoMain);

	return 0;
}

//previous
/*
float tmp1075_raw_to_celsius(uint16_t rawData) {
	uint8_t magnitude;
	uint8_t fraction;
	rawData = rawData >> 4;

	float sign = 1;
	if(rawData & 0x0800) { // or (rawData & (1 << 11)), which is better to show masking?
		sign = -1;

		rawData -= 1;
		rawData = ~rawData;
	}
	
	magnitude = (uint8_t)((rawData & 0x0FF0) >> 4);
	fraction = (uint8_t)(rawData & 0x000F);

	float celsius = (float)magnitude;
	
	float fractionSum = 0;
	if(fraction & (1 << 3)) {
		fractionSum += 0.5;
	} else if (fraction & (1 << 2)) {
		fractionSum += 0.25;
	} else if (fraction & (1 << 1)) {
		fractionSum += 0.125;
	} else if (fraction & (1 << 0)) {
		fractionSum += 0.0625;
	}

	celsius += fractionSum;
	celsius *= sign;
	return celsius;
}
*/

tmp1075_info_t tmp1075_raw_divide(uint16_t rawData) {
	uint8_t magnitude, fraction;
	rawData = rawData >> 4;

	uint8_t sign = 0;
	if(rawData & 0x0800) { // or (rawData & (1 << 11)), which is better to show masking?
		sign = 1;

		rawData -= 1;
		rawData = ~rawData;
	}
	
	magnitude = (uint8_t)((rawData & 0x0FF0) >> 4);
	fraction = (uint8_t)(rawData & 0x000F);

	float fractionSum = 0;
	if(fraction & (1 << 3)) {
		fractionSum += 0.5;
	}
	if (fraction & (1 << 2)) {
		fractionSum += 0.25;
	}
	if (fraction & (1 << 1)) {
		fractionSum += 0.125;
	}
	if (fraction & (1 << 0)) {
		fractionSum += 0.0625;
	}

	uint16_t fractionDigits = fractionSum * 10000; //0.0625 * 10000 = 625, I need 0625 to print
	//printf("%u\n", fractionDigits);

	tmp1075_info_t rinfo1 = {
		.sign = sign,
		.wholeNum = magnitude,
		.fractionNum = fractionDigits
	};

	return rinfo1;
}

void printTemperature(tmp1075_info_t info) {
	char firstNum[5];
	char secondNum[5];

	if(info.sign == 1) { printf("-"); }
	intToString((uint16_t)info.wholeNum, firstNum);
	intToString(info.fractionNum, secondNum);
	printf("%s.", firstNum);
	if(info.fractionNum < 1000 && info.fractionNum > 99) { printf("0"); }
	printf("%s'C\n", secondNum);
}
