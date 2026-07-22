//Ammar Mohammed, 2026-07-21, Timer/Counter1 w/ Compare Match A interrupt & prescaler, Blink LED 250ms
//OC1A pin at PB1
#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum {
	normal, //00 disconnected OC1A, OC1B
	toggle, //01
	clear,  //10 OC1A / OC1B (output LOW)
	set     //11 OC1A / OC1B (output HIGH)
} compare_output_mode_nonPWM_t;

typedef enum {
	no_clock,	//000
	prescale_1,	//001
	prescale_8,	//010
	prescale_64,	//011
	prescale_256,	//100
	prescale_1024,	//101
	falling_edge,	//110
	rising_edge	//111
} clock_select_bits_t;

int main() {
	//Enable global interrupt
	sei();

	//Enable Timer/Counter1, Output Compare A Match Interrupt Enable
	TIMSK1 |= (1 << OCIE1A);

	//Select clock with clk_io / 1024 prescaler
	//16MHz / 1024 = 15,625 counter cycles per second; 15625 / 4 = 3906.25
	//16MHz / 256 = 62,500; 62,500 / 4 = 15,625 <-- nice integer instead of floating-point
	TCCR1B |= (prescale_256 << CS10);

	//Toggle Pin when Comparison valid
	TCCR1A |= (toggle << COM1A0);

	//Need to have comparison value stored
	OCR1A |= (15625 << OCR1AL0); //16-bit value!!!

	//How to reset counter after comparison?

	//Do I need to enable output of PORTB1 pin?
	DDRB |= (1 << DDB1);

	while(1) {}

	return 0;
}

ISR(TIMER1_COMPA_vect) {
	//what needs to be here if using OC1A pin? Just counter reset?
	TCNT1 &= 0x0000; //clear counter?
}
