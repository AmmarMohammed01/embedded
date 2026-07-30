## One-liner
ATmega328p project in which external interrupt button increments counter to change duty cycle of PWM signal controlling brightness of LED.

## About

ATmega328p connected to an LED at Arduino Uno R3 IO9 or ATmega328p PB1 (OC1A).

16-bit Timer/Counter1 is responsible for generating a PWM signal.

The PWM signal affects the brightness of the light. The duty cycle is set to different intervals to achieve this.

A button is attached to Arduino Uno R3 IO2 or ATmega328p PD2 (INT0).

The button triggers an External Interrupt on the ATmega328p which increments a counter starting at 0.

- When counter is 0: 0% LED brightness.
- When counter is 1: 25% LED brightness.
- When counter is 2: 50% LED brightness.
- When counter is 3: 75% LED brightness.
- When counter is 4: 100% LED brightness.

## References
Page 70 - Alternate Functions of Port D
- PD2 - INT0 External Interrupt 0
- PD3 - INT1 External Interrupt 1

Page 54 - EIRCA
Page 55 - EIMSK

Page 59 - How to configure I/O pins
- Reviewing how to set input

## Challenges
### Button Debouncing

### Current Leakage to On-Board LED
- Solved by setting pin as output but LOW
