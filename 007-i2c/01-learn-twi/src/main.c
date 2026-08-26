/*
Ammar Mohammed
2026-08-08
Learn I2C, TWI.

Next steps:
- Make sure negative values are handled (2s complement)
- Make sure celsius conversion is correct, or if there is a loss of data since float not used
- Make a printf(), easier formatting
*/
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "usart.h"
#include "helper.h"
#include "my_i2c.h"

#define TMP1075_ADDR 0x48

int main() {
	usart_init(MYUBRR);

	//SCL Frequency = (CPU Frequency / (16 + 2(TWBR) x PrescalerValue)

	//TMP1075 Init
	TWBR = 3; //for a SCL frequency of 400kHz w/ prescaler value of 4
	TWSR = (1 << TWPS0); // TWI Prescaler Bits, value 4, NOTE: FORGOT TO ADD THIS LINE BACK

	//START CONDITION
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTA);
	while(!(TWCR & (1 << TWINT))); //wait for status code that START is set

	//read status code
	uint8_t status0 = TWSR & 0xF8; //mask first 5 bits for status, last 3 bits as 0

	//send SLA+W
	uint8_t addressPacket = TMP1075_ADDR << 1; //0x48 << 1 = 0x90 (100 1000 << 1 = 1001 0000)
	TWDR = addressPacket;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT)));
	uint8_t status1 = TWSR & 0xF8;

	//write 0x00 to TMP1075 pointer register
	uint8_t pointerAddress = 0x00; //inside TMP1075
	TWDR = pointerAddress;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT))); 
	uint8_t status2 = TWSR & 0xF8;

	char statusStr[5];
	usart_print("Start:");
	intToString(status0, statusStr);
	usart_print(statusStr); //prints out 8: START CONDITION

	usart_print("Second:");
	intToString(status1, statusStr);
	usart_print(statusStr); //USED TO PRINT 32, now 24: SLA+W TRANSMITTED, ACK RECEIVED

	usart_print("Third:");
	intToString(status2, statusStr);
	usart_print(statusStr); //USED TO PRINT OUT 48, now 40: DATA BYTE TRANSMITTED, ACK RETURNED

	//REPEATED START CONDITION - to put into read mode
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTA);
	while(!(TWCR & (1 << TWINT)));
	uint8_t status3 = TWSR & 0xF8;

	//SEND SLA+R
	addressPacket = (TMP1075_ADDR << 1) + 1; //0x48 << 1 = 0x90 (100 1000 << 1 = 1001 0000) , 0x90 + 1 = 0x91
	TWDR = addressPacket;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT)));
	uint8_t status4 = TWSR & 0xF8;

	usart_print("Fourth:");
	intToString(status3, statusStr);
	usart_print(statusStr); //16: REPEATED START TRANSMITTED

	usart_print("Fifth:");
	intToString(status4, statusStr);
	usart_print(statusStr); //64: SLA+R TRANSMITTED; ACK RECEIVED

	//READ 1ST BYTE
	uint8_t msb, lsb;
	TWCR = (1 << TWEN)
	     | (1 << TWINT)
	     | (1 << TWEA); //reason for ACK bit generation, we need to tell the TMP1075 that we got the byte and want more
	while(!(TWCR & (1 << TWINT)));
	uint8_t status5 = TWSR & 0xF8;
	msb = TWDR;

	//READ 2ND BYTE
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT)));
	uint8_t status6 = TWSR & 0xF8;
	lsb = TWDR;

	// Finish the read and release the bus
	TWCR = (1 << TWINT) |
	       (1 << TWEN)  |
	       (1 << TWSTO);

	usart_print("Sixth:");
	intToString(status5, statusStr);
	usart_print(statusStr); //GOT 88

	usart_print("Seventh:");
	intToString(status6, statusStr);
	usart_print(statusStr); //GOT 88

	//PRINT DATA
	uint16_t initialData = ((uint16_t)msb << 8) | lsb;

	char msbStr[5];
	intToString((uint16_t)msb, msbStr);
	usart_print(msbStr);

	char lsbStr[5];
	intToString((uint16_t)lsb, lsbStr);
	usart_print(lsbStr);


	char tempStr[10];
	intToString(initialData, tempStr);
	usart_print(tempStr);

	char celsiusStr[5];
	char fahrenheitStr[5];

	while(1) {
		uint16_t rawTempData = i2c_read_twobytes();
		intToString(rawTempData, tempStr);
		usart_print("Raw Data:");
		usart_print(tempStr);

		uint16_t celsius = rawTempData >> 8;
		intToString(celsius, celsiusStr);
		usart_print("Celsius:");
		usart_print(celsiusStr);

		float fahrenheit = ((float)celsius * 1.8) + 32;
		intToString((uint16_t)fahrenheit, fahrenheitStr);
		usart_print("Fahrenheit:");
		usart_print(fahrenheitStr);

		_delay_ms(1000);
	}
	return 0;
}

/*
Output Results
Start:
8
Second:
24
Third:
40
Fourth:
16
Fifth:
64
Sixth:
80
Seventh:
88
255 //SDA is read HIGH both times because nothing is pulling signal to ground
255
65535
Raw Data:
6272
Celsius:
24
Fahrenheit:
75
Raw Data:
6272
Celsius:
24
Fahrenheit:
75
Raw Data:
6256
Celsius:
24
Fahrenheit:
75
*/
