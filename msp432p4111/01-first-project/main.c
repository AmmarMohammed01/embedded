#include "msp.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	while(1);
}

/*
2026-09-16
I connected the MSP432P4111 to USB port.
I pressed "build".
I pressed "flash".
I pressed "debug".
I stepped, paused, resumed, and terminated the debugger.
I looked at the registers: found SP and PC.
I went to View > Memory Browser. I searched 0x00000000 and 0x00000004.
*/
