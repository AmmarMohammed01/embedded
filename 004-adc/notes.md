# Notes
## Process
Date: 2026-07-16
Reading page 217-220: 23.9 Register Description (for ADC)

- Off the bat, the ADCL & ADCH are important as it stores the data.
- The DIDR0 makes me wonder what pins are analog pins on the ATmega328p (look at datasheet)
    - I am able to find 6 analog pins A5-A0
    - They are part of PORTC.
    - They don't take up same pins as designated Arduino digital pins
        - _I just found out they can be used as digital pins!_
        - *these are digital pins 14-19 (A0-A5 respectively)*
- _Just learned ATmega328p has internal temperature sensor (page 215)_
- ***I think I should learn interrupts and timers first, since ADCSRA seems to talk about interrupts and clock cycles.***

### REGISTERS
---
[23.9.1] ADMUX - ADC Multiplexer Selection Register
---

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
| - | - | - | - | - | - | - | - |
| REFS1 | REFS0 | ADLAR | - | MUX3 | MUX2 | MUX1 | MUX0 |

#### Refeerence selection bits
- Sets what **Voltage Reference** is used.
- There are other pins on ATmega328p datasheet: AREF, AVCC, AGND
- I need to learn more about _Analog Reference Volatage_

| REFS1 | REFS0 | Voltage Reference Selection |
| - | - | - |
| 0 | 0 | AREF, internal VREF turned off |
| 0 | 1 | AVCC with external capacitor at AREF pin |
| 1 | 0 | Reserved |
| 1 | 1 | Internal 1.1V voltage reference with external capacitor at AREF pin |

#### ADLAR
- ADC Left Adjust Result
- Just decides what side (left or right) the 10-bits of data are placed in the 16-bits in the two registers.
    - More info at 23.9.3 ADC Data Register.

#### MUX
- Analog Channel Selection Bits
- These bits select which Analog Input is connected to the ADC
    - ***ONLY ONE ANALOG INPUT CAN BE CONNECTED TO ADC INPUT AT A TIME***

| MUX3:0 | Single Ended Input |
| ------ | ------------------ |
| 0000 | ADC0 |
| 0001 | ADC1 |
| 0010 | ADC2 |
| 0011 | ADC3 |
| 0100 | ADC4 |
| 0101 | ADC5 |
| .... | .... |
* More mux codes on Page 218.


[23.9.2] ADCSRA - ADC Control and Status Register A
---
- ADC Enable, ADC Start Conversion, ADC Interrupt pin settings...

[23.9.3] ADCL & ADCH - ADC Data Register
---
- Has 10-bits of data. 2^10 is 1024 values: \[0,1023\]
- ADLAR, controls how the 10 bits are adjusted across two 8-bit registers.
    - ADLAR controls via ADMUX bit
    - ADLAR = 1, left adjusted result
    - ADLAR = 0, right adjusted result

[23.9.4] ADCSRB - ADC Control and Status Register B
---

[23.9.5] DIDR0 - Digital Input Disable Register
---
- only use Bit 5:0 for ADC5D:ADC0D
- *set to logic 1* to disable digital input buffer on corresponding ADC pin
- it reduces power consumption during analog signal input, as it won't write to digital input buffer
