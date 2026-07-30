/*
Ammar Mohammed
2026-07-29
Learning to generate PWM signals using ATmega328p.
External Interrupt increments counter changing duty cycle of PWM signal affecting LED brightness.

Goal:
- Change PWM duty cycle with button press.
	- 1st press: 25%
	- 2nd press: 50%
	- 3rd press: 75%

- Is 0% and 100% possible?
*/

#include <avr/io.h>
#include <avr/interrupt.h>

int dutyModeSetting = 0;

int main(void) {
	DDRB = (1 << DDB1); // PB1 (OC1A) as output

	//explicitly set pin 5 as OUTPUT LOW
	DDRB |= (1 << DDB5);
	PORTB &= ~(1 << PORTB5);

	DDRD &= ~(1 << DDD2); // PD2 (INT0) as input

	EICRA = (1 << ISC01) | (1 << ISC00); // rising edge of INT0 generates interrupt request
	EIMSK = (1 << INT0); // enable external interrupt 0

	TCCR1A = (1 << COM1A1)        // Non-inverting PWM
	       | (1 << WGM11);

	TCCR1B = (1 << WGM13)
	       | (1 << WGM12)
	       | (1 << CS10);         // No prescaler

	ICR1 = 15999;                 // TOP
	// OCR1A = 7999;                 // ~50% duty cycle
	OCR1A = 0;

	// 0 to 15999 is 16000 counts
	// One PWM period takes 16000 / 16000000 = 1ms, meaning 1kHz is PWM frequency
	// Output goes HIGH at 0, then LOW after 7999. Resets after 15999. 50% duty cycle

	//
	sei(); //enable global interrupts

	while (1) {
	}

	return 0;
}

ISR(INT0_vect) {
	dutyModeSetting++;
	if(dutyModeSetting == 0 || dutyModeSetting == 5) {
		dutyModeSetting = 0;
		OCR1A = 0; //0%
	}
	else if (dutyModeSetting == 1) {
		OCR1A = 3999; //25%
	}
	else if (dutyModeSetting == 2) {
		OCR1A = 7999; //50%
	}
	else if (dutyModeSetting == 3) {
		OCR1A = 11999; //75%
	}
	else if (dutyModeSetting == 4) {
		OCR1A = 15999; //100%
	}
}
