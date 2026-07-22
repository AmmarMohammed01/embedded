/*
Ammar Mohammed
2026-07-22
Blink LED every 250ms using ClearTheCounter Timer/Counter Mode of Operation
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#define TOGGLE_MODE 1
#define PRESCALER_256 4
#define CTC_MODE 1

int main() {
	//Enable Compare Output Mode for Channel A in non-PWM
	TCCR1A |= (TOGGLE_MODE << COM1A0); //set toggle on Compare Match for OC1A pin

	//Set CTC waveform generation mode bit, set prescaler divisor 256
	TCCR1B |= (CTC_MODE << WGM12) | (PRESCALER_256 << CS10);

	//16,000,000 / 256 = 62,500 counts per second. Counter is 16-bit, counts 65,536 vals. 250ms is (62,500 / 4 = ) 15,625 counts.
	OCR1A = 62500;

	//Enable Timer/Counter1 Output Compare Match A Interrupt
	TIMSK1 |= (1 << OCIE1A);

	//Set global interrupts
	sei();

	//Set output for PORTB Pin 1 - OC1A
	DDRB |= (1 << DDB1);

	while(1) {
	}

	return 0;
}
