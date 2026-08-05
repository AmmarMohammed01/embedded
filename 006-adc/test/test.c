#include <stdio.h>
#include "helper.h"
#define STR_SIZE 10

int main() {
	//int myNum = 123;
	int myNum = 0;
	char myNumStr[10];
	intToString(myNum, myNumStr);
	printf("%s\n", myNumStr);
	reverseString(myNumStr);
	printf("%s\n", myNumStr);
	return 0;
}
