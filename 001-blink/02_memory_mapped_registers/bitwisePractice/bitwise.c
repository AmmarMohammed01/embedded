#include <stdio.h>
#include <stdint.h>

void printBitwise(uint8_t);

int main() {
	uint8_t myByte = 0b01001010;
	printf("%d = ", myByte);
	printBitwise(myByte);
	printf("\n");
	return 0;
}

void printBitwise(uint8_t byte)
{
	for(int i = 7; i >= 0; i--) {
		if (byte & (1 << i)) {
			printf("1");
		}
		else {
			printf("0");
		}
	}
}
