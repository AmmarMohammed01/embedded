#include <avr/io.h>
#include <stdint.h> //dtostrf()
#include <stdlib.h>
#include <util/delay.h>

#include "adc.h"
#include "uart.h"
#include "helper.h"

#define VOLT_SOURCE 5.0 //5V power

int main() {
	uart_init(MYUBRR);

	ADC_init(ADC_PS8);
	ADC_setResultAdjust(ADC_ADJUST_RIGHT);
	ADC_setVoltageRef(ADCVOLT_AVCC);
	ADC_setChannel(ADC_CHANNEL0);

	while(1) {
		uint16_t data = ADC_read();
		char dataStr[10];
		intToString(data, dataStr);

		uart_print("ADC: ");
		uart_print(dataStr);
		uart_print(", ");

		float voltage = data * VOLT_SOURCE;
		voltage /= 1024.0;

		//print out floating-point voltage
		dtostrf(voltage, 1, 2, dataStr);
		uart_print(dataStr);
		uart_print(" volts, ");

		float temperatureC = (voltage - 0.5) * 100; // (voltage - 500mV offset) * 100
		//print out floating-point temperatureC
		dtostrf(temperatureC, 1, 2, dataStr);
		uart_print(dataStr);
		uart_print("'C, ");

		float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
		//print out floating-point temperatureF
		dtostrf(temperatureF, 1, 2, dataStr);
		uart_print(dataStr);
		uart_print("'F\r\n");

		_delay_ms(1000);
	}

	return 0;
}
