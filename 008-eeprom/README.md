# Learning EEPROM
Date: 2026-09-10

## Process

```bash
mkdir 008-eeprom
cd 008-eeprom
mkdir src include
touch src/main.c src/eeprom.c include/eeprom.h
touch compile_flag.txt
```

In main.c, I started off with main(), return 0, while(1), and including avr/io.h.

Next, I included eeprom.h, created the header definition in eeprom.h too.

Then, I open the ATmega328p datasheet. Go to eeprom section.
- Table of Contents (p. 289)
- Section 7. AVR Memories > 7.4 EEPROM Data Memory (p. 19).
- Section 7. AVR Memories > 7.6 Register Description (p. 20).
- 7.6.1, 7.6.2, 7.6.3 deal w/ EEPROM registers.
- 7.6.4, 7.6.5, 7.6.6 deal w/ GPIO registers.

EEPROM Registers
- address reg (9 bits, 1-bit in high byte, 8-bit in low byte).
    - 2^9 means 512 combinations.
    - EEAR is initially UNDEFINED, MUST SET AN INITIAL VALUE!!!
    - but datasheet says: EEAR8 is unused in ATmega328p, must always be written to 0
    - I guess that leaves us with 2^8 options. 0 to 255?
        - I am a little confused: if there is 1KB of EEPROM, how do I access each byte with only 256 addresses?
- data reg.
    - before write operation, data is stored in EEDR
    - after read operation, data is read from EEDR
- control reg.
    - EEMPE: Master Write Enable
        - Set to 1. If EEPE is set to 1 right after, EEMPE set to 1 makes hardware responsible that EEPE gets cleared after 4 clock cycles.
        - If set to 0, setting EEPE does nothing
    - EEPE: Write Enable
        - set this to 1 after address and data are correctly set up.

On page 22,
- void EEPROM_write(unsigned int uiAddress, unsigned char ucData);

I was planning to use:
- void eeprom_write(char address_byte, char data_byte);
- Is unsigned int a byte on ATmega328p? I guess not, that would just be uint8_t.

Finished writing eeprom.c driver. Next, write application code to interact with EEPROM.
- Example: LED and button to remember LED_STATE (on, off) when Arduino reboots.
- Example: Remember color of RGB LED. Button to cycle between (Red, green, blue)
