/*
Ammar Mohammed
2026-07-29
Learning to generate PWM signals using ATmega328p
*/

#include <avr/io.h>

int main(void) {
	DDRB = (1 << DDB1);          // PB1 (OC1A) as output

	TCCR1A = (1 << COM1A1)        // Non-inverting PWM
	       | (1 << WGM11);

	TCCR1B = (1 << WGM13)
	       | (1 << WGM12)
	       | (1 << CS10);         // No prescaler

	ICR1 = 15999;                 // TOP
	OCR1A = 7999;                 // ~50% duty cycle
	//OCR1A = 3999; //25% duty cycle

	// 0 to 15999 is 16000 counts
	// One PWM period takes 16000 / 16000000 = 1ms, meaning 1kHz is PWM frequency
	// Output goes HIGH at 0, then LOW after 7999. Resets after 15999. 50% duty cycle

	while (1) {
	}

	return 0;
}
