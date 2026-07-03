#include "led.h"
#include <avr/io.h>

//LED at IO13/SCK
void led_init(void) {
	DDRB |= (1 << DDB5);
}

void led_on(void) {
	PORTB |= (1 << PORTB5);
}

void led_off(void) {
	PORTB &= ~(1 << PORTB5);
}

void led_toggle(void) {
	PORTB ^= (1 << PORTB5);
}
