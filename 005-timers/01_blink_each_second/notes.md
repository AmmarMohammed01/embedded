# Notes
## About
Trying to learn Timers for the ATmega328p.
Looking at the datasheet, there are **many** sections about differnt type of timers.
I think I should start with 8-bit Timer/Counter0 with PWM
Timers are what allow for PWM - Pulse Width Modulation.

First idea I need to understand: do timers have anything to do with delays, or is it mainly just PWM?

Usually when looking at registers:
- find out how to enable features
- find out how to get the data
- if register bit count is larger than databus, need to do more read/writes, followed by bit shifting

## References
ATmega328p Datasheet.
- 10.6 Watchdog System Reset
- 10.8 Watchdog Timer
- 14. 8-bit Timer/Counter0 with PWM [page 74-88]
- 15. 16-bit Timer/Counter1 with PWM
- 16. Timer/Counter0 and Timer/Counter1 Prescalers
- 17. 8-bit Timer/Counter2 with PWM and Asynchronous Operation

avr/iom328p.h
- Q1: Where to find all interrupt vector names for ATmega328p?
- A1: Can be found on iom328p.h starting line 799.
    - Seems like 3 interrupt vectors each for 8-bit counters, 4 interrupt vectors for 16-bit counter
    - Capture Match A, Capture Match B, Overflow. Extra vector for Counter1: Capture Event

["Electronic Basics #30: Microcontroller (Arduino) Timers" by GreatScott!](https://www.youtube.com/watch?v=IdL0_ZJ7V2s)

## Thoughts
### 14.9 Register Description
14.9.1 - TCCR0A – Timer/Counter Control Register A
14.9.2 TCCR0B – Timer/Counter Control Register B
14.9.3 TCNT0 – Timer/Counter Register
14.9.4 OCR0A – Output Compare Register A
14.9.5 OCR0B – Output Compare Register B
14.9.6 TIMSK0 – Timer/Counter Interrupt Mask Register
14.9.7 TIFR0 – Timer/Counter 0 Interrupt Flag Register

### 15.11 Register Description for Timer/Counter1
15.11.9 - TIFR1 Timer/Counter1 Interrupt Flag Register
    - OCF1A: Flag set in clock cycle after TCNT1 value matches Output Compare Register A (OCR1A) value.
    - OCF1A: Automatically cleared after **compare match A interrupt vector** executed.
    - OCF1A: Can also be cleared by writing logic 1 to its bit location.

15.11.4 TCNT1H and TCNT1L, Timer/CouNTer1 HIGH & LOW (value)
15.11.5 OCR1AH and OCR1AL, Output Compare Register 1 A

15.11.8 TIMSK1 – Timer/Counter1 Interrupt Mask Register
- Enable Overflow Interrupt

15.11.1 TCCR1A – Timer/Counter1 Control Register A
- Need to enable wafeform generation
- I would like to use normal generation, so since bits are 0 by default, no need to change

15.11.2 TCCR1B – Timer/Counter1 Control Register B
- Default for clock selection is no clock source (Timer/Counter stopped)
- I will choose option for no prescaling
