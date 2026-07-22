/*
Program: Change compare value while running to change the blink rate
Ammar Mohammed
2026-07-22
*/

#include <avr/io.h>
#include <avr/interrupt.h>

int main() {
	TCCR1A = (1 << COM1A0); //Enable Compare Output Mode for Channel A in non-PWM

	TCCR1B = (1 << WGM12) //set CTC
	       | (1 << CS12); //prescaler 256

	OCR1A = 15624; //0 to 15624 is 15625 counts

	DDRB = (1 << DDB1); //OC1A output
	PORTB = 0; //All LOW

	TIMSK1 = (1 << OCIE1A); //enable output compare match A interrupt
	sei(); // enable interrupts

	while(1) {
	}

	return 0;

}

ISR(TIMER1_COMPA_vect) {
	if(OCR1A == 15624) {
		OCR1A = 62499;
	}
	else {
		OCR1A = 15624;
	}
}
