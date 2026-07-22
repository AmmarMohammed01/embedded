/*
Generate a 1kHz interrupt, print every 1000 interrupts
Ammar Mohammed
2026-07-22
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>

#include "usart.h"

volatile uint16_t interruptCounter = 0;
uint8_t timesReached1000 = 0;

int main() {
	TCCR1A = (1 << COM1A0); //Enable Toggle Mode for OC1A pin

	TCCR1B = (1 << WGM12) //set CTC
	       | (1 << CS11); //prescaler 8

	OCR1A = 1999; //0 to 1999 is 2000 counts

	DDRB = (1 << DDB1); //OC1A output
	PORTB = 0; //All LOW

	TIMSK1 = (1 << OCIE1A); //enable output compare match A interrupt
	sei(); // enable interrupts

	usart_init(MYUBRR);

	while(1) {
		if(interruptCounter >= 1000) { //use to have (interruptCounter == 1000)
			interruptCounter = 0;
			timesReached1000++;
			//printPhrase("1000", 5);
			usart_transmit('1');
		}
	}
	return 0;
}

ISR(TIMER1_COMPA_vect) {
	interruptCounter++;
}
