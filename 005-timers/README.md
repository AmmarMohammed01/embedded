# TIMERS

## 2026-09-13

Timers go together with interrupts.

### Hardware Timers Available

How many timers does ATmega328p have? Three.
- 8-bit:
    - Timer/Counter0
        - Section 14, page 74-88
    - Timer/Counter2
        - Section 17, page 116-134
- 16-bit:
    - Timer/Counter1
        - Section 15, page 89-113

All the timers support PWM.

Timer/Counter2 supports Asynchronous Operations. What are Asynchronous Operations?
- info here...


### Timer Interrupt Modes

Go to ~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/avr/include/avr/iom328p.h

Search "timer"

At line 820, interrupt vector definitions for timers appear.

Every timer has COMPA, COMPB, and OVF vectors.
An additional interrupt vector called CAPT belongs exclusively to 16-bit Timer/Counter 1

Meaning of each timer interrupt vector:
- COMPA & COMPB (Interrupt on Compare):
    - Timer interrupt occurs when the counter reaches the value of comparison
    - Think of it like "if (counter_val == some_num) { do_interrupt(); }"

- OVF (Interrupt On Overflow):
    - When ever the timer/counter counts a full cycle, from 0 to 65535 (16-bit) or 0 to 255, and returns to 0 (maybe?), activate the interrupt

- CAPT

### How to choose a prescaler?

A prescaler is ...

Here is how to calculate what prescaler to use.

f_cpu: CPU frequency (Hz)
f_new: Frequency after prescalling (Hz)

f_cpu / prescaler = f_new

It depends on how many counts per second you want for your timer.

An 8-bit timer/counter can count from 0 to 255.
This range came from 2 ^ (8 bits) = 256 numbers counter can cycle through.

A 16-bit timer/counter can count 0 to 65535.
2 ^ (16 bits) = 65536

Why do we need to prescale?

A 16MHz counter means a second is reached every 16,000,000 counts.
In other words, a 16-bit counter would have to go through a full-iteration (0 to 65535),
around 244.14 times.

Prescalers that are available:
- clk_io / 1 (no prescaling)
- clk_io / 8 (from prescaler)
- clk_io / 64 (from prescaler)
- clk_io / 256 (from prescaler)
- clk_io / 1024 (from prescaler)

16,000,000 Hz / 1024 = 15625 Hz
16,000,000 Hz / 256 = 62500 Hz
16,000,000 Hz / 64 = 250000 Hz
16,000,000 Hz / 8 = 2000000 Hz

With the 1024 prescaler, during one full-iteration of 16-bit counter
65536 / 15625 = 4.19s can be counted
