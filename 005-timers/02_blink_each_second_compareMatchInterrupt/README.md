## Steps
- Read datasheets to find what registers to use.
- Reminder set pin to output: PB1 is IO9

### Circuit
- Connect GND (mcu) to GND rail (breadboard)
- Use 10k ohm resistor
- Connect anode of LED to IO9 (mcu) -> PB1 -> OC1A
- Connect cathode of LED to GND rail (breadboard)

## Challenges
How to work with 16-bit registers?
- Set bits using the TCNT1 definition in AVR/iom328p.h
    - Already defined as _SFR_MEM16(0x84)

How to reset counter after comparison?
- Just clear bits: &= and 0x0000; //set all bits to 0
