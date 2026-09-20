//2026-09-16
// main.c: blink on-board blue LED
#include "msp.h"

#define peripheral_offset 0x40004C00
#define p2out_offset 0x03
#define p2dir_offset 0x05
#define p2sel0_offset 0x0B
#define p2sel1_offset 0x0D

#define P2OUT *((volatile char*)(peripheral_offset + p2out_offset))
#define P2DIR *((volatile char*)(peripheral_offset + p2dir_offset))
#define P2SEL0 *((volatile char*)(peripheral_offset + p2sel0_offset))
#define P2SEL1 *((volatile char*)(peripheral_offset + p2sel1_offset))

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	P2SEL1 &= ~(1 << 2); P2SEL0 &= ~(1 << 2); //set p2.2 port function to gpio
	P2DIR |= (1 << 2); //set p2.2 direction to output
	P2OUT |= (1 << 2); //set p2.2 output to HIGH

	volatile unsigned int i;
	while(1){
	    for(i = 0; i < 500000; i++){} //busy-loop delay
	    P2OUT ^= (1 << 2);
	}
}
