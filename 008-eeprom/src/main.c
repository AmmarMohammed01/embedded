/*
Ammar Mohammed
2026-09-10
ATmega328p: Learn EEPROM

MCU receives a button input that toggles an LED. The LED state (ON, OFF) is saved in EEPROM.
The next time the MCU boots the LED will start at the previously saved state.
*/

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "eeprom.h"
#include "led.h"
#include "button.h"
#include "usart.h"
#include "helper.h"

#define EEPROM_ADDRESS 1
#define TIME_DELAY_MS 2000
#define LED_STATE_BIT 0

typedef enum buttonState {
	LOW = 0,
	HIGH = 8 // ACTIVE HIGH
} button_state_t;

unsigned char current_led_state = 0;

int main(void) {
	// Initialize drivers
	eeprom_init();
	led_init();
	button_init();
	//usart_init(MYUBRR);

	current_led_state = eeprom_read(EEPROM_ADDRESS); //what address to store led_state?

	if (current_led_state & (1 << LED_STATE_BIT)) {
		led_on();
		//usart_print("INIT LED ON\r\n");
	}
	else {
		led_off();
		//usart_print("INIT LED OFF\r\n");
	}

	while(1) {
		_delay_ms(2000);
		//usart_print("IN LOOP\r\n");
		int button_state = (int)button_read();
		/*THIS RETURNS 8 WHEN PRESSED, 0 WHEN NOT PRESSED
		Oh I get it now:
		0000 1000
		The one is placed there because (1 << PINB3), I am returning 1 in the bit position 3

		if (button_state == 8) //one way to fix is make HIGH = 8

		if (button_state) //probably another method since any non-zero if true
		*/


		//char button_state_str[5];
		//intToString(button_state, button_state_str);
		//usart_print(button_state_str);
		//usart_print("\r\n");

		// if(button_state == HIGH) {
		if(button_state == HIGH) {
			//usart_print("button high\r\n");
			_delay_ms(TIME_DELAY_MS);
			led_toggle();

			current_led_state ^= (1 << LED_STATE_BIT);
			eeprom_write(EEPROM_ADDRESS, current_led_state);
		}
	}

	return 1;
}
