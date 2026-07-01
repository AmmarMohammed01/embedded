#include <util/delay.h>
#include "led.h"
#include "button.h"

int main(void) {
	button_init();
	led_init();
	led_off(); //led_on();

	while(1) {
		_delay_ms(500);
		if(button_read()) {
			led_toggle();
		}
	}
	return 0;
}
