#include "led.h"
#include <avr/io.h>

//LED at IO13/SCK
void led_init(void) {
	DDRB |= (1 << DDB5); //Set pin to OUTPUT
}

void led_on(void) {
	PORTB |= (1 << PORTB5); //BIT-OR, 0010 0000
}

void led_off(void) {
	PORTB &= ~(1 << PORTB5); //BIT-AND BIT-NOT, 1101 1111
}

void led_toggle(void) {
	PORTB ^= (1 << PORTB5); //BIT-XOR, if bits different, set to 1
	//  0010 0000 <-- led on
	//^ 0010 0000
	//= 0000 0000

	//  1010 0101 <-- led on 5th index
	//^ 0010 0000
	//= 1000 0101 <-- worked out, only bit 5 changed

	//0s that were same remained 0 in result
	//1s that differed from 0 of XOR resulted in 1
}
