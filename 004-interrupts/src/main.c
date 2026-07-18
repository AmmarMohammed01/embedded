#include "interrupt.h"
#include <avr/io.h>

ISR(INT0_vect){
	PORTB ^= (1 << PORTB5);
}

int main() {
	DDRB |= (1 << DDB5); //set LED pin output
	DDRD &= ~(1 << DDD2); //set PD2 to input for INT0

	interrupt_init();
	sei();

	while(1) {

	}

	return 0;
}
