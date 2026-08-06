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
	LowLevel = 0, // better practice for enum value names: INTERRUPT_LOW_LEVEL, INTERRUPT_ANY_CHANGE, etc.
	AnyChange = 1,
	FallingEdge = 2,
	RisingEdge = 3
} SenseControl_t;

typedef enum {
	INTERRUPT0 = 0,
	INTERRUPT1 = 1
} Interrupt_t

void interrupt_init(Interrupt_t interruptNum, SenseControl_t senseControl);
#endif
