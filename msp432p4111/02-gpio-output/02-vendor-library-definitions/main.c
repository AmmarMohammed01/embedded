//2026-09-20
#include "msp.h"

// Eclipse IDE Shortcut to Line #: CTRL+L
//File: C:/ti/ccs1120/ccs/ccs_base/arm/include/msp432p4111.h
//line 576, DIO_PORT_INTERRUPTABLE_TYPE struct
//line 636, DIO_PORT_Not_Interruptable_Type
//line 664, DIO_PORT_Odd_Interruptable_Type
//line 690, DIO_PORT_Even_Interruptable_Type
//line 1407-1412, P[A-E] DIO_PORT_Interruptable_Type and PJ DIO_PORT_Not_Interruptable_Type
//line 1413-1422, P[1-10] ODD & EVEN interruptable types

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	P2->SEL0 &= ~(1 << 1); P2->SEL1 &= ~(1 << 1); //set p2.1 port function as gpio
	P2->DIR |= (1 << 1); //set p2.1 direction as output
	P2->OUT |= (1 << 1); //set p2.1 output as HIGH

	volatile unsigned int i;
	while(1){
	    for(i = 0; i < 250000; i++){
	    }
	    P2->OUT ^= (1 << 1);
	}
}
