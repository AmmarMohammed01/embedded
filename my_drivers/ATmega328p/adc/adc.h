/*Ammar Mohammed, 2026-08-06, ADC driver for ATmega328P DIP*/
#ifndef __ADC_H__
#define __ADC_H__
#include <avr/io.h>
#include <stdint.h>

typedef enum {
	ADCVOLT_AREF = 0,
	ADCVOLT_AVCC = 1,
	ADCVOLT_RESERVED = 2,
	ADCVOLT_INTERNAL = 3,
} ADC_Vref_Select_t;

typedef enum {
	ADC_ADJUST_RIGHT = 0,
	ADC_ADJUST_LEFT = 1,
} ADC_Adjust_Result_t;

typedef enum {
	ADC_CHANNEL0 = 0,
	ADC_CHANNEL1 = 1,
	ADC_CHANNEL2 = 2,
	ADC_CHANNEL3 = 3,
	ADC_CHANNEL4 = 4,
	ADC_CHANNEL5 = 5,
	//ADC_CHANNEL6 = 6,
} ADC_Channel_t; //only targeting adc channels available on DIP ATmega328P

typedef enum {
	ADC_PS2 = 1,
	ADC_PS4 = 2,
	ADC_PS8 = 3,
	ADC_PS16 = 4,
	ADC_PS32 = 5,
	ADC_PS64 = 6,
	ADC_PS128 = 7,
} ADC_Clock_Prescaler_t;

void ADC_init(ADC_Clock_Prescaler_t prescaler);

void ADC_setChannel(ADC_Channel_t channel);
void ADC_setResultAdjust(ADC_Adjust_Result_t adjustMode);
void ADC_setVoltageRef(ADC_Vref_Select_t vref);

uint16_t ADC_read();

void ADC_disable();

#endif
