/*
Ammar Mohammed
2026-07-29
Learning to generate PWM signals using ATmega328p
*/

#include <avr/io.h>

int main(void) {
	// Enable output for OCR1A pin
	DDRB = (1 << DDB1); // OC1A output
	PORTB = 0; // All LOW

	// Set Waveform Generation Mode bits
	TCCR1A = (1 << COM1A1) | // non-inverting mode: clear OC1A at compare match, set OC1A at BOTTOM
		 //(1 << COM1A0) | // Toggle OC1A on compare match in Fast PWM
		 (1 << WGM11) | (1 << WGM10); // Fast PWM using TOP as OCR1A
	
	TCCR1B = (1 << WGM13) | (1 << WGM12) // Fast PWM using TOP as OCR1A
	       | (1 << CS10); //No prescaling

	// Output Compare Value
	OCR1A = 32768; //16-bit can count 65,536 values, set half
	//OCR1A = 16383; //16-bit can count 65,536 values, set fourth

	while(1) {}

	return 0;
}
