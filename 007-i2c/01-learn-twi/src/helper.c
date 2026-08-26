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
