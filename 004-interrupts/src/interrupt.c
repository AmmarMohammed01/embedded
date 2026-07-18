/*Ammar Mohammed, 2026-07-17, External Interrupt*/
#include "interrupt.h"

void interrupt_init() {
	//Enable both interrupt pins
	//PD3 is INT1
	//PD2 is INT0

	EICRA |= (sense_risingEdge << ISC10) | (sense_risingEdge << ISC00); //set INT1 and INT0 to rising edge interrupt sense control

	EIMSK |= (1 << INT1) | (1 << INT0); //enable external interrupts for both INT1 and INT0

}
