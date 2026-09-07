#include <stdio.h>
#include <stdint.h>

unsigned shift_first_bits(unsigned data, unsigned nBits);
unsigned mask_last_bits(unsigned data, unsigned nBits);
void printBits_unsigned(unsigned char * bytes);

int main() {
	printf("float: %zu\n", sizeof(float));
	printf("unsigned: %zu\n", sizeof(unsigned));
	float num = 4961.57;
	/*
	if (num & (1 << 31)) { //error: invalid operands to binary expression ('float' and 'int')
		isNegative = 1;
	}
	*/

	unsigned char * bytes = (unsigned char *) &num;

	//With this code I found out my system (MacBook) stores bytes in little endian order. What does ATmega328p use?
	//10001111 00001100 10011011 01000101 = 0x 8F 0C 9B 45 <- little endian
	//01000101 10011011 00001100 10001111 = 0x 45 9B 0C 8F <- big endian
	//bytes[0] = 0x8F
	//bytes[1] = 0x0C
	//bytes[2] = 0x9B
	//bytes[3] = 0x45
	/*
	for(int byte = 0; byte < sizeof(float); byte++) {
		for(int bit = 7; bit >= 0; bit--) {
			currentBit = bytes[byte] & (1 << bit) ? '1' : '0';
			printf("%c", currentBit);
		}
		printf(" ");
	}
	*/
	printBits_unsigned((unsigned char *)&num);

	//DIVIDE UP float num
	//SIGN
	int isNegative = 0;
	if(bytes[3] & (1 << 7))	{
		isNegative = 1;
	}
	printf("\nIs Negative: %d\n", isNegative);

	//BIASED EXPONENT
	unsigned char biasedExponent = 0;
	biasedExponent |= (bytes[3] & 0x7F) << 1; // last 7 bits of first float byte
	biasedExponent |= (bytes[2] & 0x80) >> 7; // first 1 bit of second float byte
	printf("Biased Exponent: ");
	for(int bit = 7; bit >= 0; bit--) {
		char currentBit = biasedExponent & (1 << bit) ? '1' : '0';
		printf("%c", currentBit);
	}
	printf("\n");

	uint8_t exponentVal = (uint8_t)biasedExponent - 127;
	printf("Exponent Val: %d\n", exponentVal);

	//MANTISSA is 23 bits, 1 in front implicit, could use 24-bits or 3 bytes
	/*
	char mantissa[3]; //3 bytes
	mantissa[0] = bytes[2] & 0x7F; //if I want, I can add implicit 1 here
	mantissa[1] = bytes[1];
	mantissa[2] = bytes[0];

	printf("Mantissa: ");
	for(int byte = 0; byte < sizeof(mantissa); byte++) {
		for(int bit = 7; bit >= 0; bit--) {
			currentBit = mantissa[byte] & (1 << bit) ? '1' : '0';
			printf("%c", currentBit);
		}
		printf(" ");
	}
	printf("\n");

	mantissa[0] |= 0x80; //implicit 1
	*/

	//unsigned mantissa = (bytes[2] & 0x7F) | bytes[1] | bytes[0];
	unsigned mantissa = (1 << 23) | ((bytes[2] & 0x7F) << 16) | (bytes[1] << 8) | bytes[0];
	printf("Mantissa bits: ");
	printBits_unsigned((unsigned char *)&mantissa);

	//somehow I need to left shfit mantissa by exponent amount
	//10011011 00001100 10001111 ; this has implicit 1, if I left shift by exponent w/ implicit 1, I should add one to exponent
	//1.0011011 00001100 10001111
	//10011011 00001.100 10001111; instead of left shifting, maybe I separate num to two parts. One is the whole num, the other is the fraction.

	//mantissa uses a max of 3 bytes, since I am not restricted in memory I can use uint32_t to store each part.
	//there is no 3 byte unsigned int in /Library/Developer/CommandLineTools/SDKs/MacOSX26.5.sdk/usr/include/stdint.h
	unsigned wholeNum = 0;
	unsigned fraction = 0;

	// I need to think of a good way to divide whole and fraction part of mantissa...
	//wholeNum |= (uint32_t)mantissa; //can't cast char * to unsigned int, "smaller type" compiler warning
	wholeNum = shift_first_bits((unsigned)mantissa, exponentVal+1);
	fraction = mask_last_bits((unsigned)mantissa, 24-(exponentVal+1));
	printf("Whole Num: %d\n", wholeNum);

	//print whole num bits
	printBits_unsigned((unsigned char *)&wholeNum);

	printf("Fraction: %d\n", fraction);
	printBits_unsigned((unsigned char *)&fraction);

	//interpret fraction bits. turn the fraction bits into an unsigned number.
	//TMP1075 only uses a max of 4 fraction bits. Wait, I probably could have just converted the 4 fraction bits if I just wanted to print.
	//The reason I did all of this, I already converted raw TMP1075 data to float, I needed a way to print the float.
	//0.5, 0.25, 0.125, 0.0625 -> would look like 5000, 2500, 1250, & 0625 when printed but a '.' will be sent before these values are printed

	//Current unsigned fraction bits = 00000000 00000000 00000100 10001111
	//I need a way to identify the first fraciton bit.

	/*
	 * I did work on trying to convert a float to a string for a substantial amount of time over these past 2-3 days (8/28-29-30/2026)
	 * Here is my realization:
	 * 1. I could convert the fractions bits into one unsigned integer and print it, limited to 4 bytes.
	 * 	- 2^(32) - 1 = 4,294,967,295. Since first digit only climbs to 4, discard the 10th digit. Leaves 9 digits to store floating point as unsigned int.
	 * 2. I could store the digits from the fraction bits as Binary Coded Decimal, BCD, which is 1 byte per digit
	 * 	- TMP1075 only needs to represent 4 floating point digits, so 4 bytes for 4 characters instead of 9.
	 * 3. I could convert the whole number to string first. Then multiply the fraction portion by a factor of 10 to get it as a integer to convert to string.
	 * 	- Is there a way to find how many decimal digits are in a floating point number?
	 * 	- There is a way to find how many digits are in an integer using %10 and /10.
	*/

	return 0;
}

//what if exponent is negative?
unsigned shift_first_bits(unsigned data, unsigned nBits) {
	unsigned wholeNum = data >> (24 - nBits); //24 bits from mantissa plus implicit 1. nBits + 1 b/c implicit 1.
	return wholeNum;
}

unsigned mask_last_bits(unsigned data, unsigned nBits) {
	printf("nBits: %u\n", nBits);
	unsigned maskedData = data & ((1u << nBits) - 1u);
	return maskedData;
}

void printBits_unsigned(unsigned char * bytes) {
	char currentBit;
	for(int byte = sizeof(unsigned) - 1; byte >= 0; byte--) {
		for(int bit = 7; bit >= 0; bit--) {
			currentBit = bytes[byte] & (1 << bit) ? '1' : '0';
			printf("%c", currentBit);
		}
		printf(" ");
	}
	printf("\n");
}
