# Learn Timer/Counter Mode of Operation: Clear the Counter - CTC
## About
Blink an LED.

Have it on for 250ms, off for 250ms, and repeat.

## References
- Arduino Uno R3 Circuit Schematic

- ATmega328p Datasheet
    - 16-bit Timer/Counter1 Register Descriptions

- AVR IO header file for ATmega328p
    - Timer Counter register address definitions

## Steps
Enable output on PORTB Pin 1

Enable Compare Output Mode for Channel A in non-PWM
- Table 15-2

Set Waveform Generation Mode as CTC
- Table 15-5

Select Prescaler clk / 256
- Table 15-6

Set value of Output Compare Register 1 A

Enable Timer/Counter1 Output Compare Match A Interrupt
