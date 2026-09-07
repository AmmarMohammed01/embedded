#include "tmp1075_helper.h"

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

	if(info.sign == 1) { usart_print("-"); }
	intToString((uint16_t)info.wholeNum, firstNum);
	intToString(info.fractionNum, secondNum);
	usart_print(firstNum);
	usart_print(".");
	if(info.fractionNum < 1000 && info.fractionNum > 99) { usart_print("0"); }
	usart_print(secondNum);
	usart_print("'C\r\n");
}
