#include "msp.h"

int main(void) {
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	P2->SEL0 &= ~(1 << 1); P2->SEL1 &= ~(1 << 1); //set p2.1 port function as gpio
	P2->DIR |= (1 << 1); //set p2.1 direction as output
	P2->OUT |= (1 << 1); //set p2.1 output as HIGH

	while(1){
	    for(volatile unsigned int i = 0; i < 250000; i++){
	    }
	    P2->OUT ^= (1 << 1);
	}

	return 0;
}
