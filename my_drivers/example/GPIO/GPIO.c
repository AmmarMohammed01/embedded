// 2026-11-17, Hardware Independent GPIO Driver practice, Ammar Mohammed
//#include <stdio.h> //for NULL
#include <stddef.h> //for NULL, also has size_t
#include "GPIO.h"

typedef enum {
    GPIO_NOT_INITIALIZED,
    GPIO_INITIALIZED
} GPIO_InitStatus;

static GPIO_Direction pinDirection[GPIO_PIN_COUNT];
static GPIO_InitStatus pinInitialized[GPIO_PIN_COUNT];
static GPIO_Value simulatedPinLevel[GPIO_PIN_COUNT];

GPIO_Status GPIO_init(uint8_t pin, GPIO_Direction direction) {
	//GPIO_Status status = GPIO_STATUS_SUCCESS; //don't need local status, just immediately return a value

	// check whether the pin is within the valid range (0-7)
	/*
	if (!(pin >= 0 && pin < GPIO_PIN_COUNT)) {
		return GPIO_STATUS_INVALID_PIN;
	}
	*/
	//uint8_t can never be negative, never less than 0
	if(pin >= GPIO_PIN_COUNT) {
		return GPIO_STATUS_INVALID_PIN;
	}


	// check whether direction is either GPIO_INPUT or GPIO_OUTPUT
	if(!(direction == GPIO_INPUT || direction == GPIO_OUTPUT)) {
		return GPIO_STATUS_INVALID_ARGUMENT;
	}

	// store the requested direction is in pinDirection
	pinDirection[pin] = direction;

	// mark the pin as initialized in pinInitialized
	pinInitialized[pin] = GPIO_INITIALIZED; //perhaps I could use enum here

	//return appropriate status
	return GPIO_STATUS_SUCCESS;
}

GPIO_Status GPIO_write(uint8_t pin, GPIO_Value value) {

	// validate pin number
	if(pin >= GPIO_PIN_COUNT) {
		return GPIO_STATUS_INVALID_PIN;
	}

	// validate the requested GPIO value (GPIO_LOW or GPIO_HIGH)
	if(!(value == GPIO_LOW || value == GPIO_HIGH)) {
		return GPIO_STATUS_INVALID_ARGUMENT;
	}
	//another way to write
	//if(value != GPIO_LOW && value != GPIO_HIGH)

	// check whether the pin has been initialized
	if(pinInitialized[pin] == GPIO_NOT_INITIALIZED) {
		return GPIO_STATUS_INVALID_STATE;
	}

	// check whether the pin has been configured as an output
	// previously // if (pinDirection[pin] == GPIO_INPUT) {
	if (pinDirection[pin] != GPIO_OUTPUT) {
		return GPIO_STATUS_INVALID_STATE;
	}

	// simulate writing a value
	//GPIO_Value hardwareOutputValue = value;
	simulatedPinLevel[pin] = value;

	//return the appropriate status
	return GPIO_STATUS_SUCCESS;
}

GPIO_Status GPIO_read(uint8_t pin, GPIO_Value *resultValue) {
	// validate the pin number
	if (pin >= GPIO_PIN_COUNT) {
		return GPIO_STATUS_INVALID_PIN;
	}

	// validate resultValue isn't NULL
	if (resultValue == NULL) {
		return GPIO_STATUS_INVALID_ARGUMENT;
	}

	// check whether the pin is initialized
	if (pinInitialized[pin] == GPIO_NOT_INITIALIZED) {
		return GPIO_STATUS_INVALID_STATE;
	}

	// read the simulated pin value into *resultValue
	*resultValue = simulatedPinLevel[pin];

	//return appropriate status
	return GPIO_STATUS_SUCCESS;
}
