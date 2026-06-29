#include "button.h"
#include <avr/io.h>

//button at IO2
void button_init(void) {
	DDRD &= ~(1 << DDD2); //set 2nd bit to 0/INPUT (PAGE 59)
}

unsigned char button_read(void) {
	//How to turn on PULLUP RESISTOR, when input mode, write 1 to PORTXn
	unsigned char i;

	//(PAGE 60 Section 13.2.4)
	//__no_operation();
	i = PIND;

	i &= (1 << PIND2); //check if IO2 is HIGH or LOW
	return i;
}

/*
unsigned char
1000 0100   (Example read state from PORTD)
0000 0100 & (Checking for PIN 2)
0000 0100 = (Result if PIN 2 is high)

1000 0100   (Example read state from PORTD)
0000 0100 & (Checking for PIN 2)
0000 0000 = (Result if PIN 2 is low)
*/
