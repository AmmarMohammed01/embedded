#include "helper.h"

void intToString(uint16_t num, char * strOfNum) {
	int i = 0;
	if(num == 0) {
		strOfNum[0] = '0';
		strOfNum[1] = '\0';
		return;
	}
	while(num != 0) {
		//char currentDigit = (num % 10) + 48;
		strOfNum[i] = (num % 10) + 48;
		num /= 10;
		i++;
	}
	strOfNum[i] = '\0';

	reverseString(strOfNum);
}

//static functions can only be accessed inside the file
void reverseString(char * str) {
	//find null terminator
	int i = 0;
	while(str[i] != '\0') {
		i++;
	}

	char temp;
	for(int j = 0; j < i/2; j++) {
		temp = str[j];
		str[j] = str[i - 1 - j];
		str[i - 1 - j] = temp;
	}
}

/*
first byte: int
following nibble: fraction as binary
last nibble: just 0

example:
-25 is 1110 0111 0000 0000

subtract 1, then perform 1s complement
1110 0111
-       1
---------
1110 0110

0001 1001 = 16 + 8 + 1 = 25

But what if fraction?
1110 0111 0000
-            1
--------------
1110 0110 0000 < in this case it got carried along

So what I could do:
uint16_t rawData = rawData >> 4;
Then subtract 1.
*/
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
