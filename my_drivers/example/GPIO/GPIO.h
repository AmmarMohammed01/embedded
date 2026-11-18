// 2026-11-17, Hardware Independent GPIO Driver practice, Ammar Mohammed
#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define GPIO_PIN_COUNT 8

typedef enum {
    GPIO_INPUT,
    GPIO_OUTPUT
} GPIO_Direction;

typedef enum {
    GPIO_LOW,
    GPIO_HIGH
} GPIO_Value;

typedef enum {
    GPIO_STATUS_SUCCESS,
    GPIO_STATUS_INVALID_PIN,
    GPIO_STATUS_INVALID_STATE,
    GPIO_STATUS_INVALID_ARGUMENT
} GPIO_Status;

GPIO_Status GPIO_init(uint8_t pin, GPIO_Direction direction);
GPIO_Status GPIO_write(uint8_t pin, GPIO_Value value);
GPIO_Status GPIO_read(uint8_t pin, GPIO_Value * resultValue); //used to have GPIO_Value * const resultValue.

#endif
