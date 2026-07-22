/*Ammar Mohammed, 2026-07-17 - 2026-07-18, Timers

Purpose: Blink an LED every second using the timer.
16-bit Timer/Counter1 is used.

-------

Going to use Timer/Counter1
- Need to trigger interrupt every 1 second

- Enable Overflow Interrupt
- Set No Prescaler

CPU frequency is 16MHz
16-bit Counter can count 65536 values
16,000,000 / 65536 = 244.141
So about 244 overflows
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned int overflowCount = 0;

int main() {
	//enable global interrupts
	sei();

	//Initialize LED at Arduino Pin 13
	DDRB |= (1 << DDB5); //set gpio output

	//Enable Timer/Counter1 Overflow Interrupt
	TIMSK1 |= (1 << TOIE1);

	//Select clock with no prescaling
	TCCR1B |= (1 << CS10);

	while(1) {
	}
	return 0;
}

ISR(TIMER1_OVF_vect) {
	overflowCount++;
	if(overflowCount == 244) {
		overflowCount = 0;
		PORTB ^= (1 << PORTB5); //toggle output low/high for gpio
	}
}
