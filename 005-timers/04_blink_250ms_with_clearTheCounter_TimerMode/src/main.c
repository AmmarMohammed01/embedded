/*
Ammar Mohammed
2026-07-22
Blink LED every 250ms using ClearTheCounter Timer/Counter Mode of Operation
*/

#include <avr/io.h>
//#include <avr/interrupt.h>

int main() {
	//Enable Compare Output Mode for Channel A in non-PWM
	//TCCR1A |= (TOGGLE_MODE << COM1A0); //set toggle on Compare Match for OC1A pin
	TCCR1A = (1 << COM1A0);

	//Set CTC waveform generation mode bit, set prescaler divisor 256
	//TCCR1B |= (CTC_MODE << WGM12) | (PRESCALER_256 << CS10);
	TCCR1B = (1 << WGM12) | (1 << CS12);

	//Hz is cycles per second
	//1s / 4 = 0.25s = 250ms
	//16,000,000Hz / 256 = 62,500Hz. Counter is 16-bit, counts 65,536 vals. 250ms is (62,500Hz / 4 = ) 15,625Hz.
	OCR1A = 15624; //0 to 15624 is 15625 counts

	/*
	//Enable Timer/Counter1 Output Compare Match A Interrupt
	TIMSK1 |= (1 << OCIE1A);

	//Set global interrupts
	sei();
	*/

	//Set output for PORTB Pin 1 - OC1A
	DDRB = (1 << DDB1);

	// I was facing a weird floating pin issue. On-board pin 13 LED would blink/glow faintly at the same time OC1A Pin 9 would blink. Explicitly set low.
	DDRB |= (1 << DDB5);
	PORTB &= ~(1 << PORTB5);

	while(1) {
	}

	return 0;
}
