/*
Ammar Mohammed
2026-07-30
Learning ADC
*/
#include <avr/io.h>

#include <stdint.h> //uint16_t

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
	
	ADCSRA = (1 << ADEN) | // ADC enable
		 (1 << ADSC);  // ADC start conversion
	// ADPS prescaler selector bits

	//
	while(1) {
		//I think the data register can be called as ADC/ADCW for 16-bit or ADCL & ADCH for two 8-bit registers.
		//ADC;
		int arrSize = 4;
		char adcString[arrSize];
		//memset(adcString, 0, 4);

		uint16_t adcValue = (ADCH << 8) | ADCL;

		intToString(adcValue, adcString, arrSize);

		usart_print();
	}

	return 0;
}
