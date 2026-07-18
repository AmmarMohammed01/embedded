# Notes
## About
Notes for Project 004: Interrupts
Date: 2026-07-17

## References
Reading ATmega328p Datasheet
- 11. Interrupts
- 12. External Interrupts

Viewing Arduino Uno R3 Schematic
- Pins PD3 and PD2 have alternative uses: INT1 and INT0 respectively, standing for "INTerrupt1"...

AVR LIBC Reference
https://onlinedocs.microchip.com/oxy/GUID-317042D4-BCCE-4065-BB05-AC4312DBC2C4-en-US-2/GUID-A34C71E2-85F0-465D-AB32-321079555955.html
- <avr/interrupts.h>
    - sei() and cli(): set and clear global interrupts
    - ISR(INT0_vect): interrupt service routine, tell it for which vector

## Thoughts
### 11.2.2 MCUCR - MCU Control Register
Bit 1: IVSEL - Interrupt Vector Select
- Allows you to place interrupt vector is flash memory when set to 0
- Allows you to place interrupt vector is boot memory when set to 1

Bit 0: IVCE - Interrupt Vector Change Enable
- Allows you to change IVSEL

### 12.2.1 EICRA - External Interrupt Control Register A
- Only last 4 bits
- Interrupt Sensor Control Modes are: low level, any logical change, falling edge, rising edge.

### 12.2.2 EIMSK - External Interrupt Mask Register
- Only last 2 bits
- Enable external interrupt INT1 or INT0

### 12.2.3 EIFR - External Interrupt Flag Register
- **This is what tells MCU when an interrupt happens.**
- When an edge or logic change occurs, the INTF1 or INTF0 bits are set to 1
- Programmer doesn't need to use this. Just rely on ISR()

### 12.2.4 PCICR – Pin Change Interrupt Control Register
- Not used for proj.

### 12.2.5 PCIFR – Pin Change Interrupt Flag Register
- Not used for proj.

### 12.2.6 PCMSK2 – Pin Change Mask Register 2
- Not used for proj.

### 12.2.7 PCMSK1 – Pin Change Mask Register 1
- Not used for proj.

### 12.2.8 PCMSK0 – Pin Change Mask Register 0
- Not used for proj.

## General Reminder:
- When using pins, remember to set it as output or input with data _direction_ register (like DDRB or DDRD)
- Then, do operation you want such as [set output high] PORTB |= (1 << PORTB5), or [enable interrupt on input pin] EIMSK |= (1 << INT1) | (1 << INT0);
