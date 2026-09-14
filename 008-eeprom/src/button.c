#include "button.h"

void button_init() {
	DDRB &= ~(1 << DDB3); //set IO11 as input
}

uint8_t button_read() {
	uint8_t button_state = PINB & (1 << PINB3);
	return button_state;	
}
