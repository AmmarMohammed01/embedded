/*Ammar Mohammed, 2026-07-02, Learning USART*/

//#define FOSC 1843200 // Clock speed
#define BAUD 9600
//#define MYUBRR FOSC/16/BAUD-1
#define MYUBRR F_CPU/16/BAUD-1 //F_CPU comes from AVRDUDE command during "make flash"
/* (F_CPU / (16 * 9600)) - 1 = MYUBRR <-- formula in datasheet page 146 */

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
