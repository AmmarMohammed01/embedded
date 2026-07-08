/*Ammar Mohammed, 2026-07-02, Learning USART*/

#include <util/delay.h>
#include "usart.h"
#include "led.h"
#include "helper.h"

#define BUFFER_SIZE 51

int main(void) {
	usart_init(MYUBRR);
	led_init();

	char buffer[BUFFER_SIZE] = "hello";

	while(1) {
		_delay_ms(1000);
		//printPhrase(buffer, BUFFER_SIZE);
		interpret();
	}

	return 0;
}
