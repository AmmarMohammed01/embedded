/*
Author: Ammar Mohammed
Date: 2026-06-30
*/
#include "gpio.h"
#include <avr/io.h>

//set data directional registers to input or output, input pullup
/*
DDRx
0 or 1 for input/output
pin#

Arduino Datasheet:
Digital Pins
- D13-D8 = PB5-PB0
	- LED_BUILTIN = PB5
- D7-D0 = PD7-PD0
	- TX_LED = PD5
	- RX_LED = PD4

Analog Pins
- A5-A0 = PC5-PC0
	- SCL = PC5
	- SDA = PC4
- Reset Pin = PC6
*/
void gpio_init(gpio_port_t port, uint8_t pin, gpio_io_mode_t mode) {
	switch (port) {
		case B:
			if(mode == GPIO_OUTPUT) {
				DDRB |= (1 << pin);
			}
			else if (mode == GPIO_INPUT) {
				DDRB &= ~(1 << pin);
			}
			break;
		case C:
			if(mode == GPIO_OUTPUT) {
				DDRC |= (1 << pin);
			}
			else if (mode == GPIO_INPUT) {
				DDRC &= ~(1 << pin);
			}
			break;
		case D:
			if(mode == GPIO_OUTPUT) {
				DDRD |= (1 << pin);
			}
			else if (mode == GPIO_INPUT) {
				DDRD &= ~(1 << pin);
			}
			break;
	}

}

unsigned char gpio_read(gpio_port_t port, uint8_t pin) {
	unsigned char result;
	switch (port) {
		case B:
			result = PINB & (1 << pin);
			break;
		case C:
			result = PINC & (1 << pin);
			break;
		case D:
			result = PIND & (1 << pin);
			break;
	}
	return result;
}

void gpio_write(gpio_port_t port, uint8_t pin, gpio_state_t state) {
	switch (port) {
		case B:
			if(state == GPIO_HIGH) {
				PORTB |= (1 << pin);
			}
			else if(state == GPIO_LOW) {
				PORTB &= ~(1 << pin);
			}
			else if(state == GPIO_TOGGLE) {
				PORTB ^= (1 << pin);
			}
			break;
		case C:
			if(state == GPIO_HIGH) {
				PORTC |= (1 << pin);
			}
			else if(state == GPIO_LOW) {
				PORTC &= ~(1 << pin);
			}
			else if(state == GPIO_TOGGLE) {
				PORTC ^= (1 << pin);
			}
			break;
		case D:
			if(state == GPIO_HIGH) {
				PORTD |= (1 << pin);
			}
			else if(state == GPIO_LOW) {
				PORTD &= ~(1 << pin);
			}
			else if(state == GPIO_TOGGLE) {
				PORTD ^= (1 << pin);
			}
			break;

	}
}
