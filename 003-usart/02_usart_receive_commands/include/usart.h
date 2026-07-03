/*Ammar Mohammed, 2026-07-02, Learning USART*/

#ifndef __USART_H__
#define __USART_H__

#include <avr/io.h>

//F_CPU comes from AVRDUDE command during "make flash"
#ifndef F_CPU
#error "F_CPU must be defined before including usart.h"
#endif

#define BAUD 9600UL //UL ensures unsigned long arithmetic used, avoiding integer overflow
#define MYUBRR ( (F_CPU / (16UL * BAUD)) - 1 )

void usart_init(unsigned int ubrr);
void usart_transmit(unsigned char data);
unsigned char usart_receive(void);

#endif
