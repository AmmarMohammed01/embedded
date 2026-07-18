<!-- Good README questions

1. What does this project do?
2. How is it implemented?
3. How do I build and run it?

-->

# External Interrupt Demo (ATmega328P)

## Overview

This project demonstrates configuring the ATmega328P external interrupt INT0
without using the Arduino framework. A pushbutton connected to PD2 triggers an
interrupt on the rising edge, toggling an LED connected to PB5.

## Objectives

- Configure GPIO using registers
- Configure INT0
- Enable global interrupts
- Write an Interrupt Service Routine (ISR)
- Understand interrupt vectors

## Hardware

- Arduino Uno R3 (ATmega328P)
- Pushbutton
- LED
- 220 Ω resistor
- Breadboard

## Software

- avr-gcc
- avr-libc
- Make
- avrdude

## Project Structure

```
.
├── src/
│   ├── main.c
│   └── interrupt.c
├── include/
│   └── interrupt.h
├── Makefile
└── README.md
```

## Wiring

| Signal | Arduino Pin |
|---------|-------------|
| INT0 | D2 |
| LED | D13 |
| GND | GND |

## Register Configuration

| Register | Purpose |
|----------|---------|
| DDRB | Configure LED as output |
| DDRD | Configure INT0 as input |
| EICRA | Rising edge interrupt |
| EIMSK | Enable INT0 |
| EIFR | Clear pending interrupt |
| SREG | Enable global interrupts via `sei()` |

## Build

```bash
make
```

## Flash

```bash
make flash
```

## Expected Behavior

- Press button
- Rising edge detected
- ISR executes
- LED toggles

## What I Learned

- Difference between interrupt flags and interrupt masks
- How the interrupt vector table works
<!-- - Why `volatile` is required for shared variables -->
- How `ISR(INT0_vect)` differs from a normal function

## References

- ATmega328P Datasheet
- avr-libc Documentation
