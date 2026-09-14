/*
Ammar Mohammed
2026-09-10
ATmega328p: Learn EEPROM

MCU receives a button input that toggles an LED. The LED state (ON, OFF) is saved in EEPROM.
The next time the MCU boots the LED will start at the previously saved state.
*/

#include <avr/io.h>

#include "eeprom.h"
#include "led.h"
#include "button.h"
#include "timer.h"

typedef enum buttonState {
	LOW = 0,
	HIGH = 1 // ACTIVE HIGH
} button_state_t;

int main(void) {
	// Initialize drivers
	eeprom_init();
	led_init();
	button_init();

	while(1) {
		if(button_read() == HIGH) {
			led_toggle();
		}
	}

	return 1;
}
