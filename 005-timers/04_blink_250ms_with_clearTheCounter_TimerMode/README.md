# Learn Timer/Counter Mode of Operation: Clear the Counter - CTC
## About
Blink an LED.

Have it off for 250ms, on for 250ms, and repeat.

## References
- Arduino Uno R3 Circuit Schematic
    - OC1A pin is an alternative feature of Pin 1 of PORTB (PB1)

- ATmega328p Datasheet
    - 16-bit Timer/Counter1 Register Descriptions - TCCR1A, TCCR1B, OCR1A
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

(NOT USED) Enable Timer/Counter1 Output Compare Match A Interrupt

## Lessons Learned
### 1. Interrupt Compare Match not required
I found out that to use the Output Compare Pin, an interrupt does not need to be enabled.

I would only need to enable interrupt if I need to do something in an ISR() once the compare value of the Counter is matched.

The only thing I needed to do is enable the pin as output and set it to toggle mode in TCCR1A.

### 2. Floating Pin issue for On-Board LED
Once the program runs on the MCU for a few seconds, I noticed that the on-board LED would very faintly blink every time LED connected to Pin 9 would blink.

This could have been a current leakage issue.

#### Observations

10k Ohm Resistor at Pin 9 LED

| Blink Count of Pin 9 LED | Result on Pin 13 LED|
| - | - |
| 1st | not visible |
| 2nd | very faintly blinks|
| 3rd | faintly blinks |
| 4th | faintly blinks brighter |
| ... | about the same as 4th blink |

To solve the issue I tried a few steps.

1) Replaced resistor 10k ohm with 330 ohm.

| Blink Count of Pin 9 LED | Result on Pin 13 LED|
| - | - |
| 1st | not visible |
| 2nd | not visible |
| 3rd | not visible |
| 4th | faintly blinks |
| ... | continues to faintly blink |

2) Instead of ```DDRB |= (1 << DDB1)```, I used ```DDRB = (1 << DDB1)```
This way, it should be guaranteed that DDRB pin 1 is set as output while rest of pins are set as input.

Result: on-board blinking still visible

3) Explicitly set Pin 5 of PORTB as OUTPUT and LOW
```C
//initialize
DDRB = (1 << DDB1);

//explicitly set pin 5 as OUTPUT LOW
DDRB |= (1 << DDB5);
PORTB &= ~(1 << PORTB5);
```

Result: Issue fixed! On-board LED no longer blinks.

### 3. Initializing pins
I learned that instead of setting register using |=, registers should be set with =, this way you set only the bits you need while the rest equate to 0.

```C
//initialize
DDRB = (1 << DDB1); //example 1

TCCR1B = (1 << WGM12) | (1 << CS12); //example 2
```

### 4. Output Compare Register Value
Earlier, for 1 second delay, I was setting OCR1A as 62500.

Instead, I should set it as 62499.

In CTC mode, the timer counts \[0, OCR1A\] which is ```OCR1A + 1``` counts.

So ```62501 / 62500 ≈ 1.000016 s```. Not 1s.

```
Time (s): 0  1  2  3  4  5

OCR1A   : __|``|__|``|__|``
```

LED toggles every second.
Period: 2 seconds.
Frequency: 1 / period = 0.5 Hz
