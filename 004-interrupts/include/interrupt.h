/*Ammar Mohammed, 2026-07-17, External Interrupt*/
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__
#include <avr/interrupt.h>

typedef enum {
	sense_lowLevel = 0,
	sense_anyLogicalChange = 1,
	sense_fallingEdge = 2,
	sense_risingEdge = 3
} interrupt_sense_control_t;

void interrupt_init();
#endif
