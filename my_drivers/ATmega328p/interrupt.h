/*
File: interrupt.c
Info: Ammar Mohammed 2026-08-05
Purpose: Initialize/setup external interrupts on ATmega328p
Extra: Remember to use sei() from avr/interrupt.h and ISR(INT0_vect) and ISR(INT1_vect) in main.c.
*/
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__
#include <avr/io.h>

typedef enum {
	INTERRUPT_LOW_LEVEL = 0,
	INTERRUPT_ANY_CHANGE = 1,
	INTERRUPT_FALLING_EDGE = 2,
	INTERRUPT_RISING_EDGE = 3
} SenseControl_t;

typedef enum {
	INTERRUPT0 = 0,
	INTERRUPT1 = 1
} Interrupt_t;

void interrupt_init(Interrupt_t interruptNum, SenseControl_t senseControl);
#endif
