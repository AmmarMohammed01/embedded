/*Ammar Mohammed, 2026-07-02, Learning USART*/

#include <util/delay.h>
#include "usart.h"

int main(void) {
	usart_init(MYUBRR);

	while(1) {
		_delay_ms(1000);
		usart_transmit('h');
		usart_transmit('e');
		usart_transmit('l');
		usart_transmit('l');
		usart_transmit('o');
		usart_transmit('\n');
		usart_transmit('\r'); //carriage return, or else "screen" command won't print hello at beginning of page (creates a staircase of "hello\n")
	}

	return 0;
}
