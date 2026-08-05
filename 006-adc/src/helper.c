#include "helper.h"

void intToString(uint16_t num, char * output, int strSize) {
	/*
	int digit = 1;
	while(num != 0) {
		output[digit-1] = (num % (int)pow(10, digit)) + 48; //48 is for ASCII '0'
		num /= 10;
		digit++;
	}
	*/
	//123
	int i = 0;
	while(num != 0) {
		//char currentDigit = (num % 10) + 48;
		output[i] = (num % 10) + 48;
		num /= 10;
		i++;
	}
	output[i] = '\0';

	/*
	for(int i = 0; i < strSize; i++) {
		output[i] = '';
	}
	output[strSize-1] = '\0';
	*/
}

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
//3 2 1
