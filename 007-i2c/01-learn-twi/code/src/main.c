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
#include "tmp1075_helper.h"

#define TMP1075_ADDR 0x48

int main() {
	usart_init(MYUBRR);

	//SCL Frequency = (CPU Frequency / (16 + 2(TWBR) x PrescalerValue)
	i2c_init();

	//START CONDITION
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTA);
	while(!(TWCR & (1 << TWINT))); //wait for status code that START is set

	//send SLA+W
	uint8_t addressPacket = TMP1075_ADDR << 1; //0x48 << 1 = 0x90 (100 1000 << 1 = 1001 0000)
	TWDR = addressPacket;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT)));

	//write 0x00 to TMP1075 pointer register
	uint8_t pointerAddress = 0x00; //inside TMP1075
	TWDR = pointerAddress;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT))); 

	//REPEATED START CONDITION - to put into read mode
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTA);
	while(!(TWCR & (1 << TWINT)));

	//SEND SLA+R
	addressPacket = (TMP1075_ADDR << 1) + 1; //0x48 << 1 = 0x90 (100 1000 << 1 = 1001 0000) , 0x90 + 1 = 0x91
	TWDR = addressPacket;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT)));

	//READ 1ST BYTE
	uint8_t msb, lsb;
	TWCR = (1 << TWEN)
	     | (1 << TWINT)
	     | (1 << TWEA); //reason for ACK bit generation, we need to tell the TMP1075 that we got the byte and want more
	while(!(TWCR & (1 << TWINT)));
	msb = TWDR;

	//READ 2ND BYTE
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT)));
	lsb = TWDR;

	// Finish the read and release the bus
	TWCR = (1 << TWINT) |
	       (1 << TWEN)  |
	       (1 << TWSTO);

	//PRINT DATA
	uint16_t initialData = ((uint16_t)msb << 8) | lsb;

	char msbStr[5];
	intToString((uint16_t)msb, msbStr);
	usart_print(msbStr);
	usart_print("\n\r");

	char lsbStr[5];
	intToString((uint16_t)lsb, lsbStr);
	usart_print(lsbStr);
	usart_print("\n\r");


	char tempStr[10];
	intToString(initialData, tempStr);
	usart_print(tempStr);
	usart_print("\n\r");

	char celsiusStr[5];
	char fahrenheitStr[5];

	while(1) {
		uint16_t rawTempData = i2c_read_twobytes();
		intToString(rawTempData, tempStr);
		usart_print("Raw Data: ");
		usart_print(tempStr);
		usart_print(", ");

		/*
		float celsius = tmp1075_raw_to_celsius(rawTempData);
		intToString((uint16_t)celsius, celsiusStr);
		usart_print(celsiusStr);
		usart_print("'C, ");

		float fahrenheit = ((float)celsius * 1.8) + 32;
		intToString((uint16_t)fahrenheit, fahrenheitStr);
		usart_print(fahrenheitStr);
		usart_print("'F\n\r");
		*/
		tmp1075_info_t info = tmp1075_raw_divide(rawTempData);	
		printTemperature(info);

		_delay_ms(1000);
	}
	return 0;
}

/*
 * Previous Output
25
32
6432
Raw Data: 6432, 25'C, 77'F
Raw Data: 6432, 25'C, 77'F
Raw Data: 6432, 25'C, 77'F
Raw Data: 6432, 25'C, 77'F
Raw Data: 6432, 25'C, 77'F
 *
 * Current Output
25
32
6432
Raw Data: 6432, 25.1250'C
Raw Data: 6432, 25.1250'C
Raw Data: 6432, 25.1250'C
Raw Data: 6416, 25.0625'C
Raw Data: 6432, 25.1250'C
Raw Data: 6416, 25.0625'C
Raw Data: 6432, 25.1250'C
Raw Data: 6432, 25.1250'C
Raw Data: 6432, 25.1250'C
 * */
