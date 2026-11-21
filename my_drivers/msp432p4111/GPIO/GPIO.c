// 2026-11-17, Hardware Independent GPIO Driver practice, Ammar Mohammed
#include <stddef.h> //for NULL, also has size_t
#include <stdint.h>
#include "GPIO.h"
#include "msp.h"

typedef enum {
    GPIO_NOT_INITIALIZED,
    GPIO_INITIALIZED
} GPIO_InitStatus;

typedef struct {
	volatile const uint8_t *IN;
	volatile uint8_t *OUT;
	volatile uint8_t *DIR;
	volatile uint8_t *SEL0;
	volatile uint8_t *SEL1;
	volatile uint8_t *REN;
} GPIO_PortRegisters;

typedef enum {
	GPIO_SELECT_GENERAL,
	GPIO_SELECT_PRIMARY,
	GPIO_SELECT_SECONDARY,
	GPIO_SELECT_TERTIARY
} GPIO_FunctionSelect;

// static GPIO_Direction pinDirection[GPIO_PORT_COUNT][GPIO_PIN_COUNT]; // could remove this since portRegisters.DIR is tracking this now
static GPIO_InitStatus pinInitialized[GPIO_PORT_COUNT][GPIO_PIN_COUNT];

static GPIO_Status GPIO_getPortRegisters(GPIO_Port port, GPIO_PortRegisters *resultRegisters);

GPIO_Status GPIO_init(GPIO_Port port, uint8_t pin, GPIO_Direction direction, GPIO_Value initialOutputValue) {
	if(pin >= GPIO_PIN_COUNT) {
		return GPIO_STATUS_INVALID_PIN;
	}

	if(direction != GPIO_INPUT &&
	   direction != GPIO_OUTPUT &&
	   direction != GPIO_INPUT_PULLUP &&
	   direction != GPIO_INPUT_PULLDOWN
	) {
		return GPIO_STATUS_INVALID_ARGUMENT;
	}

	// resolve the port using GPIO_getPortRegisters()
	GPIO_PortRegisters portRegisters;
	GPIO_Status portRegisterStatus = GPIO_getPortRegisters(port, &portRegisters);
	if (portRegisterStatus != GPIO_STATUS_SUCCESS) {
		return portRegisterStatus;
	}

	uint8_t pinMask = (1U << pin);

	if (direction == GPIO_OUTPUT) {
		if(initialOutputValue != GPIO_LOW && initialOutputValue != GPIO_HIGH) {
			return GPIO_STATUS_INVALID_ARGUMENT;
		}
	}
	
	// select the GPIO peripheral function using SEL0 and SEL1
	// if (functionSelect == GPIO_SELECT_GENERAL) // TODO: Ask about this, should other function selects be allowed
	// *(portRegisters.SEL0) &= ~(1 << pin); // previous implementation, fine but use pinMask now
	*(portRegisters.SEL0) &= ~pinMask;
	*(portRegisters.SEL1) &= ~pinMask;

	// configure the direction using DIR
	if (direction == GPIO_OUTPUT) {
		// *(portRegisters.DIR) = direction; // Initial implementation: this is a mistake. DIR is 8-bits. I am setting one bit. Not even selecting the correct bit.
		*(portRegisters.REN) &= ~pinMask;

		if (initialOutputValue == GPIO_HIGH) {
			*(portRegisters.OUT) |= pinMask;
		} else {
			*(portRegisters.OUT) &= ~pinMask;
		}

		*(portRegisters.DIR) |= pinMask;
	} else if (direction == GPIO_INPUT){
		*(portRegisters.DIR) &= ~pinMask;
		*(portRegisters.REN) &= ~pinMask;
	} else if (direction == GPIO_INPUT_PULLDOWN) {
		/*
		*(portRegisters.REN) &= ~pinMask; // temporarily disable resistor to prevent sudden configuration changes when setting OUT register
		*(portRegisters.OUT) &= ~pinMask;
		*(portRegisters.REN) |= pinMask;
		*(portRegisters.DIR) &= ~pinMask;
		*/
		*(portRegisters.DIR) &= ~pinMask;  // Stop driving the pin
		*(portRegisters.REN) &= ~pinMask; // Disable resistor
		*(portRegisters.OUT) &= ~pinMask; // Select pull-down
		*(portRegisters.REN) |= pinMask;  // Enable pull-down
	} else if (direction == GPIO_INPUT_PULLUP) {
		*(portRegisters.DIR) &= ~pinMask;
		*(portRegisters.REN) &= ~pinMask; // temporarily disable resistor to prevent sudden configuration changes when setting OUT register
		*(portRegisters.OUT) |= pinMask;
		*(portRegisters.REN) |= pinMask;
	}

	// pinDirection[port][pin] = direction;

	pinInitialized[port][pin] = GPIO_INITIALIZED;

	return GPIO_STATUS_SUCCESS;
}

GPIO_Status GPIO_write(GPIO_Port port, uint8_t pin, GPIO_Value value) {
	if(pin >= GPIO_PIN_COUNT) {
		return GPIO_STATUS_INVALID_PIN;
	}

	if(value != GPIO_LOW && value != GPIO_HIGH) {
		return GPIO_STATUS_INVALID_ARGUMENT;
	}

	GPIO_PortRegisters portRegisters;
	GPIO_Status portRegisterStatus = GPIO_getPortRegisters(port, &portRegisters);
	if (portRegisterStatus != GPIO_STATUS_SUCCESS) {
		return portRegisterStatus;
	}

	if(pinInitialized[port][pin] == GPIO_NOT_INITIALIZED) {
		return GPIO_STATUS_INVALID_STATE;
	}

	uint8_t pinMask = (1U << pin);

	// if (pinDirection[port][pin] != GPIO_OUTPUT) { return GPIO_STATUS_INVALID_STATE; }
	if ((*(portRegisters.DIR) & pinMask) == 0U) {
		return GPIO_STATUS_INVALID_STATE;
	}

	// actually write value to GPIO
	if (value == GPIO_HIGH) {
		*(portRegisters.OUT) |= pinMask;
	} else {
		*(portRegisters.OUT) &= ~pinMask;
	}

	return GPIO_STATUS_SUCCESS;
}

GPIO_Status GPIO_read(GPIO_Port port, uint8_t pin, GPIO_Value *resultValue) {
	if (pin >= GPIO_PIN_COUNT) {
		return GPIO_STATUS_INVALID_PIN;
	}

	if (resultValue == NULL) {
		return GPIO_STATUS_INVALID_ARGUMENT;
	}

	GPIO_PortRegisters portRegisters;
	GPIO_Status portRegisterStatus = GPIO_getPortRegisters(port, &portRegisters);
	if (portRegisterStatus != GPIO_STATUS_SUCCESS) {
		return portRegisterStatus;
	}

	if (pinInitialized[port][pin] == GPIO_NOT_INITIALIZED) {
		return GPIO_STATUS_INVALID_STATE;
	}

	// actually read value from GPIO
	// *resultValue = *(portRegisters.IN); // Initial Implementation, returns all the 8-bits. Need to return only the bit related to the pin.
	
	uint8_t pinMask = (1U << pin);
	if (*(portRegisters.IN) & pinMask) {
		*resultValue = GPIO_HIGH;
	} else {
		*resultValue = GPIO_LOW;
	}

	return GPIO_STATUS_SUCCESS;
}

static GPIO_Status GPIO_getPortRegisters(
    GPIO_Port port,
    GPIO_PortRegisters *resultRegisters
) {
	if (resultRegisters == NULL) {
		return GPIO_STATUS_INVALID_ARGUMENT;
	}

	GPIO_PortRegisters temp;

	switch (port) {
		case GPIO_PORT_1:
			temp.IN = &P1->IN;
			temp.OUT = &P1->OUT;
			temp.DIR = &P1->DIR;
			temp.SEL0 = &P1->SEL0;
			temp.SEL1 = &P1->SEL1;
			temp.REN = &P1->REN;
			break;

		case GPIO_PORT_2:
			temp.IN = &P2->IN;
			temp.OUT = &P2->OUT;
			temp.DIR = &P2->DIR;
			temp.SEL0 = &P2->SEL0;
			temp.SEL1 = &P2->SEL1;
			temp.REN = &P2->REN;
			break;

		default:
			return GPIO_STATUS_INVALID_PORT;
	}

	*resultRegisters = temp;
	return GPIO_STATUS_SUCCESS;
}
