# Learn Timer/Counter Mode of Operation: Clear the Counter - CTC
## About
Blink an LED.

Have it off for 250ms, on for 1s, and repeat.

## References
- Arduino Uno R3 Circuit Schematic
    - OC1A pin is an alternative feature of Pin 1 of PORTB (PB1)

- ATmega328p Datasheet
    - 16-bit Timer/Counter1 Register Descriptions - TCCR1A, TCCR1B, OCR1A, TIMSK1
    - I/O Register Descriptions - DDRB & PORTB

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

For ISR()
- call the output compare match 1 A interrupt vector.
- within the ISR, change the value from 15624 (250ms) to 62499 (1s) and vice-versa.

### Circuit
- Connect GND (mcu) to GND rail (breadboard)
- Use 330 ohm resistor between GND and cathode of LED
- Connect anode of LED to IO9 (mcu) -> PB1 -> OC1A
- Provide power to Arduino Uno R3 board via USB cable
```
LED(-)  LED(+)
 |       |
 |       |
330ohm   |
 |       |
 |       |
GND     IO9
```
