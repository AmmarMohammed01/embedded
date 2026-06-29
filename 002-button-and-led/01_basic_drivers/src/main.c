#include "led.h"
#include "button.h"

int main(void) {
	button_init();
	led_init();
	led_on();

	while(1) {
		for(volatile long i = 0; i < 500000; i++) {}
		if(button_read()) {
			led_toggle();
		}
	}
	return 0;
}
