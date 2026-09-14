/*
Ammar Mohammed
2026-09-14
Smart Fan:
- ADC: temperature sensor,
- timers & PWM: motor,
- I2C: OLED screen,
- UART: debugging (for now)

- GPIO, interrupts
*/
#include <avr/io.h>
#include "gpio/gpio.h"
#include "adc/adc.h"
#include "uart/uart.h"

int main(void) {
	//ADC_init(ADC_Clock_Prescaler_t prescaler);
	//gpio_init(gpio_port_t port, uint8_t pin, gpio_io_mode_t mode);
	uart_init(MYUBRR);

	while(1) {

	}
	return 0;
}
