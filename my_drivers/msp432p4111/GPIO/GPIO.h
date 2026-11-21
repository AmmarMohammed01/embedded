// 2026-11-17, Hardware Independent GPIO Driver practice, Ammar Mohammed
#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define GPIO_PIN_COUNT 8
#define GPIO_PORT_COUNT 2

typedef enum {
    GPIO_INPUT, //0
    GPIO_OUTPUT, //1
    GPIO_INPUT_PULLUP,
    GPIO_INPUT_PULLDOWN
} GPIO_Direction;

typedef enum {
    GPIO_LOW,
    GPIO_HIGH
} GPIO_Value;

typedef enum {
    GPIO_STATUS_SUCCESS,
    GPIO_STATUS_INVALID_PIN,
    GPIO_STATUS_INVALID_PORT,
    GPIO_STATUS_INVALID_STATE,
    GPIO_STATUS_INVALID_ARGUMENT
} GPIO_Status;

typedef enum {
	GPIO_PORT_1,
	GPIO_PORT_2
} GPIO_Port;

GPIO_Status GPIO_init(GPIO_Port port, uint8_t pin, GPIO_Direction direction, GPIO_Value initialOutputValue);
// DOCUMENTATION: initialOutputValue is ignored for input configurations.
// DOCUMENTATION: If GPIO_init is used to reconfigure the pin from OUTPUT HIGH/LOW to OUTPUT LOW/HIGH, a physical transition occurs

GPIO_Status GPIO_write(GPIO_Port port, uint8_t pin, GPIO_Value value);
GPIO_Status GPIO_read(GPIO_Port port, uint8_t pin, GPIO_Value * resultValue); //used to have GPIO_Value * const resultValue.

#endif
