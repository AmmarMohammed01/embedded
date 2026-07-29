# Learning PWM on ATmega328p

## Hardware
- Using an Arduino Uno R3 with on-board ATmega328p.
- Green LED.
- 330 ohm resistor.

## Ports to use
- PB1 alternate function of OC1A (Output Compare Match A output) at Arduino Uno R3 pin 9

## Reference
- ATmega328p Datasheet: To understand how to program the mcu.
- Arduino Uno R3 Circuit Schematic: To understand what pins to connect components to.
- avr/iom328p.h: to look up the interrupt vectors

## Observations
- All the timers seem to include PWM functionality.
- Going to use 16-bit Timer/Counter1 for this project.
- P. 100 Modes of Operation mentions PWM
    - Normal Mode & CTC Mode
    - PWM modes (3)
        - Fast PWM (P. 101-103)
            - Differs from other PWM since it's **single slope**.
            - Counter goes from BOTTOM to TOP, then restarts at BOTTOM.
            - Non-Inverting vs. Inverting Compare Output Modes
                - Non-Inverting: Output is CLEARED at Compare Match, SET at BOTTOM.
                - Inverting: Output is SET at Compare Match, CLEARED at BOTTOM.
            - Resolution formula on P. 101 (What does resolution mean?)
            - Counter is incremented until 3 cases; value matches:
                - a fixed value (WGM13:0 = 5, 6, 7) - fixed at 8-bit, 9-bit, or 10-bit
                - a value in ICR1 (WGM13:0 = 14)
                - a value in OCR1A (WGM13:0 = 15)
            - What is TOP?
                - Is it the highest value the counter can reach?
                - TOP has a column in WGM table on Page 109.
            - What is ICR1?
                - Input Capture Register for Timer/Counter1

        - Phase Correct PWM (P. 103-104)
        - Phase & Frequency Correct PWM (P. 104-105)

- Register Settings
    - P. 108-109 Compare Output Mode bits for PWM
    - P. 109 Waveform Generation Mode bits

- Alternate Port Functions ()
    - Page 65, PORTB, PB1 used for OC1A = Timer/Counter1 Output Compare Match A output

## Plan
- I think I will choose Waveform Generation Mode (WGM) 15. This mode is Fast PWM using OCR1A as the top value.
- WGM bits are located in TCCR1A & TCCR1B
