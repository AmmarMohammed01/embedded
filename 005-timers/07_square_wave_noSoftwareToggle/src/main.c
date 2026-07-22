/*
Generate a square wave on an output pin using hardware compare. No software toggling.
Ammar Mohammed
2026-07-22

1kHz input toggle means:
- 1ms HIGH
- 1ms LOW

Above: 1 cycle per 2ms -> 1/2*10^-3 = 0.5 * 10^3 = 500Hz
For 2ms there is a 50% duty cycle.
Means 500Hz output square wave.
*/
#include <avr/io.h>

int main() {
	TCCR1A = (1 << COM1A0); //Enable Toggle Mode for OC1A pin

	TCCR1B = (1 << WGM12) //set CTC
	       | (1 << CS11); //prescaler 8

	OCR1A = 1999; //0 to 1999 is 2000 counts

	DDRB = (1 << DDB1); //OC1A output
	PORTB = 0; //All LOW

	while(1) {}
	return 0;
}
