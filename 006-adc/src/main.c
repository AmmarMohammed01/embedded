/*
Ammar Mohammed
2026-07-30
Learning ADC
*/
#include <avr/io.h>

#include <stdint.h> //uint16_t
#include <util/delay.h>

//#include "adc.h"
#include "usart.h"
#include "helper.h"

int main() {
	//Initialize ADC

	ADMUX = (1 << REFS0); //AVcc with external capacitor at AREF pin (default for Arduino I assume, since it has cap in schematic)
	//do these need to be written. top line already sets these to zero
	/*
	ADMUX &= ~(1 << ADLAR) | //right adjust adc data
		 ~(1 << MUX3) | ~(1 << MUX2) | ~(1 << MUX1) | (1 << MUX0); //select ADC0 as input
	*/
	
	/*
	ADCSRA = (1 << ADEN) | // ADC enable
		 (1 << ADSC);  // ADC start conversion
	*/
	// ADPS prescaler selector bits
	ADCSRA = (1 << ADEN) | // ADC enable
	//ADC Prescaler Bits -> Division Factor 128; 16,000,000 Hz / 128 = 125,000 Hz
         (1 << ADPS2) |
         (1 << ADPS1) |
         (1 << ADPS0);

	usart_init(MYUBRR);

	while(1) {
		//I think the data register can be called as ADC/ADCW for 16-bit or ADCL & ADCH for two 8-bit registers.
		//ADC;
		int arrSize = 5;
		char adcString[arrSize];

		ADCSRA |= (1 << ADSC); // Start conversion
		while (ADCSRA & (1 << ADSC)); // Wait until finished (page 218, start conversion bit turns to 0 once conversion complete). Reminds me of USART.
		/*
		// x 1 x x x x x x = ADCSRA
		// 0 1 0 0 0 0 0 0 = (1 << ADSC)
		// 0 1 0 0 0 0 0 0 = ADCSRA & (1 << ADSC) --> validates TRUE

		// x 0 x x x x x x = ADCSRA
		// 0 1 0 0 0 0 0 0 = (1 << ADSC)
		// 0 0 0 0 0 0 0 0 = ADCSRA & (1 << ADSC) --> validates FALSE
		*/

		//THIS FAILS SINCE ADCL MUST BE READ BEFORE ADCH
		//uint16_t adcValue = (ADCH << 8) | ADCL;

		//THIS WORKS: ADCL IS READ FIRST, ADCH IS READ SECOND (page 219)
		uint8_t lowByte = ADCL;
		uint8_t highByte = ADCH;
		uint16_t adcValue = (highByte << 8) | lowByte;

		//THIS WORKS
		//uint16_t adcValue = ADC;

		//TEST VALUES TO SEE IF USART_PRINT() IS WORKING
		//uint16_t adcValue = 1023;
		//uint16_t adcValue = 456;

		intToString(adcValue, adcString);
		reverseString(adcString);

		usart_print(adcString);
		_delay_ms(1000);
	}

	return 0;
}
