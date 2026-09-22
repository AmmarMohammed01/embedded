#include "msp.h"
// Blink LED every 500ms, using polling
// Peripherals: GPIO, Timer_A (16-bit counter)
// 2026-09-20
// Ammar Mohammed

/*
 * Peripheral Declarations: line 1393
 * - line 1462: Timer_A0 is (Timer_A_Type *)
 * - line 1261: Timer_A_Type struct def
 *
 * Searching msp432p4111.h for "SMCLK"
 * - line 9585: #define TIMER_A_CTL_TASSEL_2 ((uint16_t)0x0200) // !< SMCLK

-- TIMER_A_CTL[SSEL] Bits --
#define TIMER_A_CTL_SSEL_OFS ( 8) // !< TASSEL Bit Offset

 * Line 9552 TIMER_A_CTL[MC] Bits
 *
 * Searching for "CCR"
 * line 1256, it is an array[5] part of the Timer_A_Type struct
 *
 * Checking MSP342 datasheet for SMCLK frequency
 * Checking system_msp432p4111.c for SMCLK frequency
 * line 67 & 71, cpu frequency is 3MHz
 *
 * Checking msp432p4111.h for CS struct def.
 * - line 1406 CS is CS_Type*
 * - line 464-484 CS_Type struct
 *
 * Read TRM for Clock Source and register descriptions
 * - page 5 TOC section 6
 * - page 378 start of section 6
 *  - p 381-392 clock source operation
 *      - p 379 SMCLK meaning
 *      - p 380 USEFUL CS Block Diagram
 *  - p 393-409 clock source registers
 *
 * SMCLK: Low-Speed Subsystem Master Clock
 *
 * Looking at the p 380 block diagram, SMCLK frequency is decided
 * by one of the SELS MUX inputs.
 *
 * The frequencies for the SELS inputs are
 * defined lines 79-85 of system_msp432p4111.c
 * Now I need to find what SELS is set to.
 *
 * Apparently, SELS and DIVS are never initialized in system_msp432p4111.c.
 * Therefore, SMCLK will have default values.
 * Checking TRM for CSCTL1 default values of SELS & DIVS.
 *
 * P. 396 CSCTL1 default vals.
 * DIVS default is 000b
 * SELS default is 011b (surprising, it's not 000b)
 * SELS 011b means it uses DCOCLK frequency. (p 397)
 *
 * system_msp432p4111.c line 308 & 322, for 3000000 system clock, DCO is set to 2MHz-4MHz range (so it will be 3MHz)
 * msp432p4111.h lines 2583-2594, CS_CTL0[DCORSEL] Bits
 *
 * How often does LED blink?
 * (TAxCCR0 + 1) / SMCLK = (30,000 + 1) / 3,000,000Hz = 10ms
 * So it's on for 10ms, off for 10ms. That is a 20ms period. 1/20ms is 50Hz.
 * Normally, human eye stops seeing blinking at 60Hz to 90Hz range.
 * Need to slow down the frequency.
 *
 * 250ms blinking on, 250ms off. 1/500ms = 2Hz
 * 250ms = (ticks + 1) / 3,000,000Hz
 * ticks = (250ms * 3,000,000Hz) - 1
 * ticks = 749,999 <-- can't fit in 16-bit counter
 *
 * Since the number can't fit in 16-bit counter,
 * a divider needs to be used to get a number that results in 250ms.
 * Check Timer_A registers in TRM for divider.
 * Page 797, input divider bits - ID. Max division is by 8.
 * msp432p4111.h TIMER_A_CTL[ID] Bits lines 9565-9577
 *
 * Input divider now set to 8.
 * 3,000,000 / 8 = 375,000Hz
 * 250ms = (ticks + 1) / 375000
 * ticks = 250ms * 375,000 - 1
 * ticks = 93749 <-- still more than 16-bits needed
 *
 * Fortunately, there is the Input Divider Expansion
 * TAIDEX supports division of 1,2,3,4,5,6,7,8 on top of Input Divider.
 * The TAIDEX bits are part of the TAxEX0 register. (p.802 - Timer_Ax Expansion 0 Register)
 * msp432p4111.h lines 9655-9676 TIMER_A_EX0[IDEX] Bits
 *
 * IDEX is /8. ID is /8.
 * 3,000,000 / 8 / 8 = 46875Hz <-- this can fit in 16-bits
 * ticks = 250ms * 46875Hz - 1
 * ticks = 11,717.75. I will set to 11,717.
 *
 * My LED is not blinking:
 * Using debugger.
 *
I think I found the problems.
TIMER_A0:

TACTL
TASSEL 01 - aclk
ID 00 - 1
MC 00 - stop

I believe it is because I had offsets, even though the options are already in the proper place.
TIMER_A0->CTL = (TIMER_A_CTL_TASSEL_2 << TIMER_A_CTL_SSEL_OFS) //set clock source to SMCLK
| (TIMER_A_CTL_MC_1 << TIMER_A_CTL_MC_OFS) //set mode control to up mode: counts 0 to TAxCCR0
| (TIMER_A_CTL_ID__8 << TIMER_A_CTL_ID_OFS);
 *
 * Fixed code:
 * TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 //set clock source to SMCLK
                  | TIMER_A_CTL_MC_1 //set mode control to up mode: counts 0 to TAxCCR0
                  | TIMER_A_CTL_ID__8;
 */

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	// setup gpio
	//BIT0 means 0x0001, equivalent to (1 << 0). To set 0th bit to 0, ~BIT0
	// (1 << BIT0) is wrong, that means you're setting the 1st bit (BIT1).
	P1->SEL0 &= ~BIT0; P1->SEL1 &= ~BIT0; //set p1.0 port function as gpio
	P1->DIR |= BIT0; //p1.0 as output
	P1->OUT |= BIT0; //p1.0 as high

	// setup Timer_A
	TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 //set clock source to SMCLK
                  | TIMER_A_CTL_MC_1 //set mode control to up mode: counts 0 to TAxCCR0
                  | TIMER_A_CTL_ID__8; //input divider set to 8. "/8"

	TIMER_A0->EX0 = TIMER_A_EX0_IDEX__8; //input divider expansion set to 8. "/8"

	// Current frequency is SMCLK_freq / 8 / 8. or SMCLK_freq / 64.

	TIMER_A0->CCR[0] = 23436; // capture/compare register. 16-bit counter. 23436 = 0x5B8C

	//polling the timer.
	while(1) {
	    if(TIMER_A0->CCTL[0] & TIMER_A_CCTLN_CCIFG) { //when interrupt flag is met
	        TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // clear the interrupt flag
	        P1->OUT ^= BIT0; //toggle p1.0 output
	    }
	}
}
