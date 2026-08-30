#include <stdio.h>

//First attempt
/*
void printBits(void * data, int numBytes) {
	for(int i = (numBytes*8)-1; i >= 0; i--) {
		if(data & (1 << i)) {
			printf("1");
		}
		else {
			printf("0");
		}
	}
	printf("\n");
}
*/

void printBits(const void * data, size_t size) {
	const unsigned char *bytes = data; //char is 1 byte, storing the address of data.
	
	for(size_t byte = size; byte-- > 0;) {
		for(int bit = 7; bit >= 0; bit--) {
			putchar( (bytes[byte] >> bit) & 1 ? '1' : '0' );
		}
		putchar(' ');
	}
	putchar('\n');
}

int main() {
	printf("int has %zu bytes\n", sizeof(int));
	printf("float has %zu bytes\n", sizeof(float));
	printf("\n");

	printf("123: ");
	//printBits((void *)132, sizeof(int));
	int i = 123;
	printBits(&i, sizeof i);
	
	printf("4321.56: ");
	//printBits((void *)4321.56, sizeof(float));
	float f = 4321.56;
	printBits(&f, sizeof f); //I get 0 10001011 0000111 00001100 01111011 = 4321.56005859375
	//I now understand why people say computers struggle with floating point
	//This video makes more sense now too: 
	/*
	TITLE: Floating Point Numbers - Computerphile
	LINK: https://www.youtube.com/watch?v=PZRI1IfStY0
	*/
	//man float -> mentions use of IEEE 754 standard

	printf("10: ");
	f = 10;
	printBits(&f, sizeof f);

	return 0;
}
