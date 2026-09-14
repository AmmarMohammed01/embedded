#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>

typedef enum {
	B,
	C,
	D
} gpio_port_t;

typedef enum {
	GPIO_INPUT,
	GPIO_OUTPUT
} gpio_io_mode_t;

typedef enum {
	GPIO_LOW,
	GPIO_HIGH,
	GPIO_TOGGLE
} gpio_state_t;

void gpio_init(gpio_port_t port, uint8_t pin, gpio_io_mode_t mode);
unsigned char gpio_read(gpio_port_t port, uint8_t pin);
void gpio_write(gpio_port_t port, uint8_t pin, gpio_state_t state);

#endif
