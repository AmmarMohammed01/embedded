#include "msp.h"
// Blink LED every 500ms, using interrupt handler
// Peripherals: GPIO, Timer_A, NVIC/interrupts (16-bit counter)
// 2026-09-21
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

----
 * 2026-09-21
 * Working with Timer A interrupt.
 * Need to learn how to use interrupts on MSP432 / ARM Cortex-M4F.
 * Understand the difference between TAIFG and CCFIG.
 * - TRM p.801 TAxIV register
 *  - Register only uses last 4-bits (16-bit total)
 *  - Register shows which interrupt is pending.
 *      - CCR1's CCIFG has higher priority than CCR6's CCIFG. CCR6's CCIFG has higher priority than TAIFG. (p.801 register table)
 *  - In the table it says TAIFG occurs when TIMER_A overflows. So that is the difference/clarification for TAIFG vs CCIFG.
 *
 * TRM p.82 NVIC - Cortex-M peripheral
 *
 * Searching for example in sdk for timer w/ interrupt:
 * - C:\ti\simplelink_msp432p4_sdk_3_40_01_02\examples\nortos\MSP_EXP432P4111\registerLevel\msp432p411x_ta0_01\msp432p411x_ta0_01.c
 * - Example code uses NVIC->ISER, TA0_0_IRQn, and __enable_irq();
 * - It also used TAIE, but I already figured that out.
 * - The bottom of the code has function void TA0_0_IRQHandler()
 *  - I think it is just a function they named, it doesn't need to be declared at top of main b/c ISR calls it.
 *      - Let me see if TA0_0_IRQHandler is defined in system_msp432p4111_ccs.c > system_init()
 *      - Nope, it is in startup_msp432p4111_ccs.c: definition, then used in vector table. startup[...].c contains reset and default handler code.
 *
 * Search msp432p4111.h for IRQ
 * - line 87-145 enum IRQn_Type
 * - line 111 TA0_0_IRQn = 8
 *
 * Interesting, in startup_msp432p4111_ccs.c,
 * the "extern" keyword is used to search for definitions/implementations
 * of the interrupt handler functions in other files.
 * But I am only defining TA0_0_IRQHandler. So by default,
 * the functions I don't define/implement are given "Default_Handler"
 * implementations, which is just an infinite while loop.
 *
 * Search msp432p4111.h for NVIC:
 * - line 6969-7164 has NVIC bits.
 *
 * Now I will read TRM about NVIC.
 * - TRM p.115-129 NVIC register descriptions
 *  - p.115:
 *      - I notice the table describes the register for IRQ #x to #y.
 *      - The TA0_0_IRQn is enum val 8. Hence, focus on IRQ 0 to 31
 *      - Registers: Set Enable, Clear Enable, Set Pending, Clear Pending, Active Bit, Priority, Software Trigger Interrupt.
 *          - Priority: 3 bits to set scale 0(highest)-7(lowest). Use IPR2 for IRQ #8
 *
 * - TRM p.82-83 NVIC description
 *  - p.82: you can set an interrupt's priority from 0-7 scale
 *
 * cmsis_ccs.h:
 * - __enable_irq macro //core function
 * - __NOP macro, makes me believe that __enable_irq is an arm assembly instruction too //core instruction
 *
 * cmsis_gcc.h:
 * - it has __attribute__ definitions, & static inline.
 * - lines 83-86 found void __enable_irq(void)!!!
 *
 * core_cm4.h
 * - lines 404-419: NVIC_Type struct
 * - line 1550: NVIC_BASE address
 * - line 1556: NVIC macro for struct pointer
 * - lines 1588-1936: NVIC functions??
 *
 * What does IRQ mean? Interrupt ReQuest. Found out by reading p.799 CCIE register of TA0CCTL0.
 * What does the nested vector part of NVIC mean?
 *
 * Is CCIFG cleared after interrupt is called?
 * TRM p.795 s19.2.6 TIMER_A interrupts
 * - My understanding of last paragraph in 19.2.6.1:
 *   Because multiple CCR's can have their own CCIFGs, the CCIFG's are cleared after an ISR.
 *
 * TRM p.789-791 s16.2.4.1 Capture Mode
 * - When CAP = 1, get the time from TAxR and (record) place that value into TAxCCRn, CCIFG is set.
 * - The two bullet points and FIgure 19-10 helped me understand capture mode.
 * TRM p.791 s16.2.4.2 Compare Mode
 * - When CAP = 0, compare value TAxR to value application placed in TAxCCRn, if equal then set CCIFG.
 *
 * msp432p4111.h line 9605 TIMER_A_CCTLN_CCIE
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
                  //| TIMER_A_CTL_IE; //interrupt enable

	TIMER_A0->EX0 = TIMER_A_EX0_IDEX__8; //input divider expansion set to 8. "/8"

	// Current frequency is SMCLK_freq / 8 / 8. or SMCLK_freq / 64.

	TIMER_A0->CCR[0] = 23436; // capture/compare register. 16-bit counter. 23436 = 0x5B8C
	TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;

	/*
	NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31); //TA0_0_IRQn = 8 found in msp432p4111.h
	// 01000(8) & 11111(31) = 01000. 1 << 8.
	 */
	NVIC_EnableIRQ(TA0_0_IRQn); //core_cm4.h
	__enable_irq(); // the code ran w/o this line. startup enabled it?

	while(1) {
	    //polling method
	    /*
	    if(TIMER_A0->CCTL[0] & TIMER_A_CCTLN_CCIFG) { //when interrupt flag is met
	        TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // clear the interrupt flag
	        P1->OUT ^= BIT0; //toggle p1.0 output
	    }
	    */
	}
}

void TA0_0_IRQHandler(void) {
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // ??? Don't need to clear CCIFG? Example SDK shows it should be done.
    P1->OUT ^= BIT0;
}
