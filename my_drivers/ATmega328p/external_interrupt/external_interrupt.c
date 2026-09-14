/*
File: interrupt.c
Info: Ammar Mohammed 2026-08-05
Purpose: Initialize/setup external interrupts on ATmega328p
Extra: Remember to use sei() from avr/interrupt.h and ISR(INT0_vect) and ISR(INT1_vect) in main.c.

Learned: Originally I was doing 
EIMSK = (1 << INT0);

I learned that if I tried to initialize INT1 earlier, it would be erased here.
Instead using this preserves prior settings:
EIMSK |= (1 << INT0)

BUG: CLEARING TWO BITS
Earlier:

```
EICRA &= ~(1 << ISC01) | ~(1 << ISC00);

1 1 1 1 1 1 0 1 [ ~(1 << ISC01) ]
1 1 1 1 1 1 1 0 [ ~(1 << ISC00) ]
--------------- | (bitwise or)
1 1 1 1 1 1 1 1 ( result 1 )

x x x x 0 0 1 1 [ EICRA ]
1 1 1 1 1 1 1 1 ( result 1 )
--------------- &
x x x x 0 0 1 1 ( result 2 ) <-- the bits don't clear!
```

Instead use:
```
EICRA &= ~( (1 << ISC01) | (1 << ISC00) );

0 0 0 0 0 0 1 0 [ (1 << ISC01) ]
0 0 0 0 0 0 0 1 [ (1 << ISC00) ]
--------------- | (bitwise or)
0 0 0 0 0 0 1 1 ( result 1 )

0 0 0 0 0 0 1 1 (result 1)
--------------- ~ (bitwise not)
1 1 1 1 1 1 0 0 ( result 2 )

x x x x 0 0 1 1 [ EICRA ]
1 1 1 1 1 1 0 0 (result 2)
--------------- & (bitwise and)
x x x x 0 0 0 0 ( result 3 ) <-- bits successfully cleared!
*/
#include "interrupt.h"

void interrupt_init(Interrupt_t interruptNum, SenseControl_t senseControl) {
	if(interruptNum == INTERRUPT0) {
		EIMSK |= (1 << INT0); // Enable interrupt at INT0

		switch(senseControl) {
			case LowLevel:
				EICRA &= ~( (1 << ISC01) | (1 << ISC00) );
				break;
			case AnyChange:
				EICRA &= ~(1 << ISC01);
				EICRA |= (1 << ISC00);
				break;
			case FallingEdge:
				EICRA &= ~(1 << ISC00);
				EICRA |= (1 << ISC01);
				break;
			case RisingEdge:
				EICRA |= (1 << ISC01) | (1 << ISC00); // Generate interrupt request at rising edge
				break;
		}

	}
	else if(interruptNum == INTERRUPT1) {
		EIMSK |= (1 << INT1); // Enable interrupt at INT1

		switch(senseControl) {
			case LowLevel:
				EICRA &= ~( (1 << ISC11) | (1 << ISC10) );
				break;
			case AnyChange:
				EICRA &= ~(1 << ISC11);
				EICRA |= (1 << ISC10);
				break;
			case FallingEdge:
				EICRA &= ~(1 << ISC10);
				EICRA |= (1 << ISC11);
				break;
			case RisingEdge:
				EICRA |= (1 << ISC11) | (1 << ISC10); // Generate interrupt request at rising edge
				break;
		}
	}

}
