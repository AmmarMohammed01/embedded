/*
Ammar Mohammed
2026-08-06
ADC Driver for ATmega328P DIP (Dual In-Line Package)
Version: 1
*/
#include "adc.h"

void ADC_init(ADC_Vref_Select_t adcVoltMode, ADC_Adjust_Result_t adcAdjustSelect, ADC_Channel_t adcChannelNum, ADC_Clock_Prescaler_t adcPrescaler) {
	ADMUX &= ~( (1 << REFS1) | (1 << REFS0) );
	ADMUX |= (adcVoltMode << REFS0);

	ADMUX &= ~(1 << ADLAR);
	ADMUX |= (adcAdjustSelect << ADLAR);

	ADMUX &= ~( (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) );
	ADMUX |= (adcChannelNum << MUX0);

	ADCSRA |= (1 << ADEN); //Enable ADC

	ADCSRA &= ~( (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) );
	ADCSRA |= (adcPrescaler << ADPS0);
}

uint16_t ADC_read() {
	//capture ADC value
	ADCSRA |= (1 << ADSC); //start adc conversion
	while(ADCSRA & (1 << ADSC)); //wait until conversion complete
	uint8_t lowByte = ADCL;
	uint8_t highByte = ADCH;
	uint16_t adcValue = (highByte << 8) | lowByte;

	return adcValue;
}

void ADC_disable() {
	ADCSRA &= ~(1 << ADEN);
}
