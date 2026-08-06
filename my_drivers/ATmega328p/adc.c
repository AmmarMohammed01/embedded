/*
Ammar Mohammed
2026-08-06
ADC Driver for ATmega328P DIP (Dual In-Line Package)
Version: 2
*/
#include "adc.h"

void ADC_init(ADC_Clock_Prescaler_t prescaler) {
	ADCSRA |= (1 << ADEN); //Enable ADC

	ADCSRA &= ~( (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) );
	ADCSRA |= (prescaler << ADPS0);
}

void ADC_setChannel(ADC_Channel_t channel) {
	ADMUX &= ~( (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) );
	ADMUX |= (channel << MUX0);

	//one-hot, also disable one pin, all others enabled
	DIDR0 = (1 << channel); //NOTE: This implementation won't work if ADC6 and ADC7 are added.
}

void ADC_setResultAdjust(ADC_Adjust_Result_t adjustMode) {
	ADMUX &= ~(1 << ADLAR);
	ADMUX |= (adjustMode << ADLAR);
}

void ADC_setVoltageRef(ADC_Vref_Select_t vref) {
	ADMUX &= ~( (1 << REFS1) | (1 << REFS0) );
	ADMUX |= (vref << REFS0);
}

uint16_t ADC_read() {
	//capture ADC value
	ADCSRA |= (1 << ADSC); //start adc conversion
	while(ADCSRA & (1 << ADSC)); //wait until conversion complete
	/*
	uint8_t lowByte = ADCL;
	uint8_t highByte = ADCH;
	uint16_t adcValue = (highByte << 8) | lowByte;
	return adcValue;
	*/
	return ADC; //16-bit register provided in avr/iom328p.h
}

void ADC_disable() {
	ADCSRA &= ~(1 << ADEN);
}
