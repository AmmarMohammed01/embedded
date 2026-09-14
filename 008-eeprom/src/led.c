#include "led.h"

void led_init() {
	DDRB |= (1 << DDB5); //output PB5
}

void led_on() {
	PORTB |= (1 << PORTB5); // high
}

void led_off() {
	PORTB &= ~(1 << PORTB5); // low
}

void led_toggle() {
	PORTB ^= (1 << PORTB5); // xor toggle
}

/*
Toggle bit

xx0xxxxx (PORTB)
00100000 (1 << PORTB5)

^ is the XOR operator.

If both are different, then 1.
If both are same, then 0.
*/
