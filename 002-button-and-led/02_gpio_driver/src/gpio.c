/*
Arduino has:
- pinMode(pin, input/output);
- digitalRead(pin);
- digitalWrite(pin, HIGH/LOW);
- analogRead(analogPin);
- analogWrite();

In Project 001, to use a pin I defined a macro dereferencing the PORTB address.
Then I wrote a bit to the 5th position to interface Arduino Pin 13.

*/
#include "gpio.h"

void gpio_pin_mode() {}

void gpio_write() {}

void gpio_read() {}
