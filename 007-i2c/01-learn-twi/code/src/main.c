/*
Ammar Mohammed
2026-08-08
Learn I2C, TWI.

Next steps:
- Make sure negative values are handled (2s complement)
- Make sure celsius conversion is correct, or if there is a loss of data since float not used
- Make a printf(), easier formatting
*/
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "usart.h"
#include "helper.h"
#include "my_i2c.h"
#include "tmp1075_helper.h"

#define TMP1075_ADDR 0x48

int main() {
	usart_init(MYUBRR);

	//SCL Frequency = (CPU Frequency / (16 + 2(TWBR) x PrescalerValue)
	i2c_init();

	//PRINT DATA
	uint16_t initialData = i2c_read_twobytes();

	char tempStr[10];
	intToString(initialData, tempStr);
	usart_print(tempStr);
	usart_print("\n\r");

	char celsiusStr[5];
	char fahrenheitStr[5];

	while(1) {
		uint16_t rawTempData = i2c_read_twobytes();
		intToString(rawTempData, tempStr);
		usart_print("Raw Data: ");
		usart_print(tempStr);
		usart_print(", ");

		float fahrenheit = tmp1075_raw_to_fahrenheit(rawTempData);
		intToString((uint16_t)fahrenheit, fahrenheitStr);
		usart_print(fahrenheitStr);
		usart_print("'F, ");

		tmp1075_info_t info = tmp1075_raw_divide(rawTempData);	
		printTemperature(info);

		_delay_ms(1000);
	}
	return 0;
}

/*
Current Output
Raw Data: 6544, 78'F, 25.5625'C
*/
