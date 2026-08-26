#include "my_i2c.h"

void i2c_init() {
	//TMP1075 Init
	TWBR = 3; //for a SCL frequency of 400kHz w/ prescaler value of 4
	TWSR = (1 << TWPS0); // TWI Prescaler Bits, value 4
}

uint16_t i2c_read_twobytes() {
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

	return ( ((uint16_t)msb << 8) | lsb );
}
