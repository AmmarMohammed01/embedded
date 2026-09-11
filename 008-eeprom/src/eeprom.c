#include "eeprom.h"

void eeprom_init() {
	EECR &= ~( (1 << EEPM1) | (1 << EEPM0) ); //EEPROM Control Register
	//erase and write as one atomic action
}

void eeprom_write(unsigned int uiAddress, unsigned char ucData) {
	while(EECR & (1 << EEPE)); // wait for completion of previous write

	/* Set up address and data registers */
	EEAR = uiAddress;
	EEDR = ucData;

	//if working w/ interrupts
	//uint8_t sreg = SREG; //interrupt code
	//cli();

	EECR |= (1 << EEMPE); // Write logical one to EEMPE: Master Write Enable

	//Within 4 clock cycles, EEPE should be set to 1. So condition is met. Set bit to 1 takes place 1 instruction after.
	// An interrupt betweeen (1 << EEMPE) and (1 << EEPE) can cause write to fail!
	EECR |= (1 << EEPE); // Start eeprom write by setting EEPE: Write Enable

	//should I clear EEMPE here?
	//EECR &= ~(1 << EEMPE); // no, EEMPE is cleared by hardware after 4 cycles

	//SREG = sreg; //restore prev. state of interrupt
}

unsigned char eeprom_read(unsigned int uiAddress) {
	while (EECR & (1 << EEPE)); // make sure write is finished

	EEAR = uiAddress; // set address

	EECR |= (1 << EERE); // start read

	return EEDR; // return value in data reg.
}
