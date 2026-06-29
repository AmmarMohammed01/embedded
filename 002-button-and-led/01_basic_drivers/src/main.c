#include <stdint.h>
#include "led.h"

int main(void) {
	led_init();
	led_on();

	while(1) {
		led_toggle();
		for(volatile long i = 0; i < 500000; i++) {}
	}
	return 0;
}
