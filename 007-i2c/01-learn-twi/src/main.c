/*
Ammar Mohammed
2026-08-08
Learn I2C, TWI.
*/
#include <avr/io.h>
#include <stdint.h>

#include "usart.h"
#include "helper.h"

#define TMP1075_ADDR 0x48

int main() {
	usart_init(MYUBRR);

	//TWI
	//SCL Frequency = (CPU Frequency / (16 + 2(TWBR) x PrescalerValue)

	/*
	TWBR = 3; //for a SCL frequency of 400kHz w/ prescaler value of 4

	TWCR = (1 << TWEN) | //enable TWI
	       (1 < TWINT)

	TWSR = (1 << TWPS0); // TWI Prescaler Bits, value 4
	*/

	//TMP1075 Init
	TWBR = 3;
	TWSR = (1 << TWPS0); // TWI Prescaler Bits, value 4, NOTE: FORGOT TO ADD THIS LINE BACK
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTA);
	while(!(TWCR & (1 << TWINT))); //wait for status code that START is set

	//read status code
	uint8_t status0 = TWSR & 0xF8; //mask first 5 bits for status, last 3 bits as 0

	uint8_t addressPacket = TMP1075_ADDR << 1; //0x48 << 1 = 0x90 (100 1000 << 1 = 1001 0000)
	TWDR = addressPacket;
	TWCR = (1 << TWEN) | (1 << TWINT); // | (1 << TWSTA);
	while(!(TWCR & (1 << TWINT))); //wait for status code that START is set
	uint8_t status1 = TWSR & 0xF8;

	uint8_t pointerAddress = 0x00;
	TWDR = pointerAddress;
	TWCR = (1 << TWEN) | (1 << TWINT); // | (1 << TWSTA);
	while(!(TWCR & (1 << TWINT))); //wait for status code that START is set
	uint8_t status2 = TWSR & 0xF8;

	char statusStr[5];
	usart_print("Start:");
	intToString(status0, statusStr);
	usart_print(statusStr); //prints out 8

	usart_print("Second:");
	intToString(status1, statusStr);
	usart_print(statusStr); //USED TO PRINT 32, now 24

	usart_print("Third:");
	intToString(status2, statusStr);
	usart_print(statusStr); //USED TO PRINT OUT 48, now 40

	while(1) {
		/*
		uint16_t celsius = TWDR >> 8; //value in celsius
		intToString();
		reverseString();
		usart_print();
		*/

		/*
		//Send start condition
		TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

		while(!(TWCR & (1 << TWINT))); //wait for status code that START is set

		if ((TWSR & 0xF8) != START)
			ERROR(); // ?

		TWDR = SLA_W;
		*/
	}
	return 0;
}
