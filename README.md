# Embedded Projects
## About
Learning bare-metal embedded C programming by using Arduino Uno R3.

This repo shows my journey: moving from Arduino Framework to writing bare-metal C code for the ATmega328p microcontroller.

Peripherals/Concepts explored: GPIO, UART, Interrupts, Timers, ADC.

## Project List - Learning Embedded C
### 001-blink
- Started 2026-06-26
- Completed 2026-06-27

### 002-button-and-led
- 2026-06-30

### 003-usart
- 2026-07-02

### 004-interrupts
- 2026-07-17: External Interrupt.

### 005-timers
- 2026-07-18: Blink an LED each second using 16-bit Timer/Counter1 w/ overflow interrupt and no prescaling.
- 2026-07-21: Blink an LED each second using 16-bit Timer/Counter1 w/ compare match interrupt w/ 1024 divisor prescaling.
- 2026-07-21: Blink an LED every 250ms using 16-bit Timer/Counter1 w/ compare match interrupt w/ 256 divisor prescaling.
- 2026-07-22: Blink an LED every 250ms using 16-bit Timer/Counter1 w/ compare match w/ 256 prescaler & CTC.
- 2026-07-22: Blink an LED (off 250ms, on 1s) using Timer/Counter1, compare match interrupt, 256 prescaler, & CTC.
- 2026-07-22: Generate a 1kHz interrupt. Meaning, cause an interrupt every 1ms. Print something every 1000 interrupts.
- 2026-07-22: Generate a square wave on an output pin using hardware compare. No software toggling.
- 2026-07-29: Start learning PWM.

### 006-adc
- Started 2026-07-16.
- Paused 2026-07-17, learn interrupts and timers first.
- 2026-07-30: Resume learning about ADC.
- 2026-08-04/05: Successfully print ADC value.

Potential future topics: I2C, SPI, Bootloader, sleep modes, fuse bits, watchdog timer.

## Project List - Other Projects

### 001-Temperature-Server
- 2026-07-28: Learned how to use Socket Streams on the Server and Client side.
