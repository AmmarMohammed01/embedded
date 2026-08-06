/*
Ammar Mohammed
2026-08-06
ADC Driver for ATmega328P DIP (Dual In-Line Package)
Version: 1
*/
#include "adc.h"

void ADC_init(ADC_Vref_Select_t adcVoltMode, ADC_Adjust_Result_t adcAdjustSelect, ADC_Channel_t adcChannelNum, ADC_Clock_Prescaler_t adcPrescaler) {
	/*
	switch(adcVoltMode) {
		case ADCVOLT_AREF:
			ADMUX &= ~( (1 << REFS1) | (1 << REFS0) );
			break;
		case ADCVOLT_AVCC:
			ADMUX &= ~(1 << REFS1);
			ADMUX |= (1 << REFS0);
			break;
		case ADCVOLT_RESERVED:
			ADMUX |= (1 << REFS1);
			ADMUX &= ~(1 << REFS0);
			break;
		case ADCVOLT_INTERNAL:
			ADMUX |= (1 << REFS1) | (1 << REFS0);
			break;
	}
	*/
	ADMUX &= ~( (1 << REFS1) | (1 << REFS0) );
	ADMUX |= (adcVoltMode << REFS0);

	/*
	switch(adcAdjustSelect) {
		case ADC_ADJUST_RIGHT:
			ADMUX &= ~(1 << ADLAR);
			break;
		case ADC_ADJUST_LEFT:
			ADMUX |= (1 << ADLAR);
			break;
	}
	*/
	ADMUX &= ~(1 << ADLAR);
	ADMUX |= (adcAdjustSelect << ADLAR);

	/*
	switch(adcChannelNum) {
		case ADC_CHANNEL0:
			ADMUX &= ~( (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) );
			break;
		case ADC_CHANNEL1:
			ADMUX &= ~( (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) );
			ADMUX |= (1 << MUX0);
			break;
		case ADC_CHANNEL2:
			ADMUX &= ~( (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) );
			ADMUX |= (1 << MUX1);
			break;
		case ADC_CHANNEL3:
			ADMUX &= ~( (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) );
			ADMUX |= (1 << MUX1) | (1 << MUX0);
			break;
		case ADC_CHANNEL4:
			ADMUX &= ~( (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) );
			ADMUX |= (1 << MUX2);
			break;
		case ADC_CHANNEL5:
			ADMUX &= ~( (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) );
			ADMUX |= (1 << MUX2) | (1 << MUX0);
			break;
		case ADC_CHANNEL6:
			ADMUX &= ~( (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) );
			ADMUX |= (1 << MUX2) | (1 << MUX1);
			break;
	}
	*/
	ADMUX &= ~( (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) );
	ADMUX |= (adcChannelNum << MUX0);

	ADCSRA |= (1 << ADEN); //Enable ADC

	/*
	switch(adcPrescaler) {
		case ADC_PS2:
			ADCSRA &= ~( (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) );
			break;
		case ADC_PS4:
			ADCSRA &= ~( (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) );
			ADCSRA |= (1 << ADPS1);
			break;
		case ADC_PS8:
			ADCSRA &= ~( (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) );
			ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
			break;
		case ADC_PS16:
			ADCSRA &= ~( (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) );
			ADCSRA |= (1 << ADPS2);
			break;
		case ADC_PS32:
			ADCSRA &= ~( (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) );
			ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
			break;
		case ADC_PS64:
			ADCSRA &= ~( (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) );
			ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
			break;
		case ADC_PS128:
			ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
			break;
	}
	*/
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
