//Ammar Mohammed, 2026-06-30
#include "button.h"
#include "gpio.h"

void button_init(void) {
	//DDRD &= ~(1 << DDD2); //IO2 INPUT
	gpio_init(D, 2, GPIO_INPUT);
}

unsigned char button_read(void) {
	//return (PIND & (1 << PIND2));
	return gpio_read(D, 2);
}
