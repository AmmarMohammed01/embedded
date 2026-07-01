#include "led.h"
#include "gpio.h"

void led_init(void) {
	//DDRB |= (1 << DDB5); //LED at IO13/SCK OUTPUT
	gpio_init(B, 5, GPIO_OUTPUT);
}

void led_on(void) {
	//PORTB |= (1 << PORTB5);
	gpio_write(B, 5, GPIO_HIGH);
}

void led_off(void) {
	//PORTB &= ~(1 << PORTB5);
	gpio_write(B, 5, GPIO_LOW);
}

void led_toggle(void) {
	//PORTB ^= (1 << PORTB5);
	gpio_write(B, 5, GPIO_TOGGLE);
	
}
