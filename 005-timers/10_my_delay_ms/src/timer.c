#include "timer.h"

void timer_init() {
	//TCCR1A;

	//normal port operation
	//COM1A1, COM1A0, COM1B1, COM1B0 all set to 0
	//	- not using OC1A/OC1B for pin output
	
	//WGM11, WGM10 set to 0
	//	- OC1A/OC1B disconnected

	//Set prescaler
	TCCR1B = (1 << CS11) | (1 << CS10); //prescaler 64
}

//blocking time function
void timer_delay_ms(int time_ms) {
	int x = (250000 * time_ms) / 1000;

	OCR1A = x; // NOTE: what if value is greater than 65535?

	// Have something happen when timer finishes
	// interrupt or flag

	// write a no_op instruction? write a volatile instruction?
}

/*
I want to count 50ms for button input delay.

I have 16MHz CPU clock.

If I apply prescaler of 1024: 16,000,000 / 1024 = 15,625 Hz.

15,625 counts for 1 second.

How many ms are in 1 second.
milli is 10^-3

So 1000ms = 1s.
In other words, 15,625 counts for 1000ms.

x        50ms
------ = ------
15,625   1000ms

(50 * 15,625) / 1000 = x
x = 781,250 / 1000
x = 781.25 <-- this is a floating point number.

Let me try a different prescaler.

Prescaler of 256

x        50ms
------ = ------
62,500   1000ms

(50 * 62,500) / 1000 = x
x = 3,125,000 / 1000
x = 3,125 <-- an integer. This is 50ms

What happens when I want to count 2s or 2000ms? (w/ prescaler 256)

x        2000ms
------ = ------
62,500   1000ms

(2000 * 62,500) / 1000 = x
x = 125,000 counts
^ in this case, the timer/counter will overflow almost 2 times.

Can 16,000,000 be represented as a 32-bit integer? Yes.
2^31 - 1 = 2,147,483,647
I can actually use "unsigned" integers since there are no negative counts

x            2000ms
---------- = ------
16,000,000   1000ms

(16000000 * 2000) / 1000 = x
x = 32,000,000 counts

32,000,000 / 65536 = 488.28125 overflows for 2 seconds

FIND A COMBINATION THAT GETS AN INTEGER FOR 1ms:
Use prescaler of 8 or 64.
16,000,000Hz / 64 = 250,000Hz

x           1ms
--------- = ------
250,000Hz   1000ms

250,000 / 1,000 = 250 counts for 1ms
*/
