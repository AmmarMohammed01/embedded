/*Ammar Mohammed, 2026-07-02, Learning USART
Modified 2026-07-30: added usart_print()
Modified 2026-08-05: changed usart_print() to avoid reliance on msg length
*/
#include "usart.h"

void usart_init(unsigned int ubrr) {
	/*Set baud rate*/
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	/*Enable receiver and transmitter*/
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/*Set frame format: 8-bit char data, 2 stop bits*/
	UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

void usart_transmit(unsigned char data) {
	/* Wait for empty transmitt buffer */
	while(!(UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data*/
	UDR0 = data;
}

unsigned char usart_receive(void) {
	/* Wait for data to be received */
	while(!(UCSR0A & (1<<RXC0)));
	/* Get and return data from buffer */
	return UDR0;
}

//Function that prints multiple characters at a time
//void usart_print(char* message, unsigned int msgLength) {
void usart_print(char* message) {
	/*
	for (int i = 0; i < msgLength; i++) {
		usart_transmit(message[i]);
	}
	*/
	while(*message) { //terminates at '\0' b/c \0 is just 0x00 in mem.
		usart_transmit(*message);
		message++;
	}
	//usart_transmit('\n');
	//usart_transmit('\r');
}
