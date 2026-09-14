# Learning EEPROM
## Date: 2026-09-10

### Process

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

For the LED, I will just write a simple led.c driver.
- I remember GPIO uses the PORTx and DDRx for output.
- Look at the Arduino Uno R3 circuit schematic for pin numbers
    - I want to control pin 13: IO13 is PB5
- Look at ATmega328p datasheet to refresh memory on how to use the registers
    - Section 13 I/O Ports (p. 58) > 13.4 Register Description (p. 72)
    - Going off of memory, PORT sets input/output. DDR sets ON/OFF when output. (Nope, it is the other way around)

---

What does debounce mean?
- "To remove the small ripple of current that forms when a mechanical switch is pushed in an electrical circuit and makes a series of short contacts" (Wiktionary, Creative Commons Attribution/Share-Alike License)

What does depress mean?
- To press down. (The American Heritage® Dictionary of the English Language, 5th Edition)
- To push downwards or inwards.
- The "de-" prefix doesn't mean undo here.
- Opposite of depress would be to "release the pushbutton"

How to debounce a pushbutton
- https://docs.arduino.cc/built-in-examples/digital/Debounce/
- In the example, they use millis(). How does millis() work?
    - My guess: increment a global variable every clock cycle whenever the counter increments. The counter and variable start at 0.
    - The variable is an unsigned long
- Implementation: ~/Library/Arduino15/packages/arduino/hardware/avr/1.8.8/cores/arduino/wiring.c
    - volatile unsgined long
    - Oh so they do use an interrupt for their timer. An overflow ISR is used.
- Earlier I was reading the AVR _delay_ms() implementation:
    - ~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/avr/include/util/delay.h
    - ~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/avr/include/util/delay_basic.h

Idea I would like to try w/ an oscilliscope:
- Depress a button and observe how long the button input is unstable
- Use the result to understand how long the debounce delay should typically be

## DATE 2026-09-13

### Toggle an LED
How to toggle an LED?

Normal button setup:
```c
if (buttonState == HIGH) {
    LED_ON();
}

else if (buttonState == LOW) {
    LED_OFF();
}
```

The above doesn't really need a microcontroller. It can be done with circuitry.

An action is being defined for when a button is depressed and when a button is released.

Toggle an LED:
```c
if (buttonState == HIGH) {
    LED_TOGGLE(); // use the ^ (toggle) bit operator to change pin output state
}
```

^ just define the behavior for when the button is depressed.

No behavior should exist for when the button is released.

```c
if (buttonState == HIGH) {
    if (LED_state == ON) {
        LED_state = OFF;
    }
    else {
        LED_state = ON;
    }
}
```

The above implementation controls a variable rather than directly changing the pin output connecting to the LED.

Perhaps the first solution is cleaner and concise.

### Implement timer to debounce button

How would one debounce a button connected to an interrupt?

Have I debounced a button in bare-metal programming before?
- I believe I have debounced a button in Arduino Framework
- I have seen that in my very early code after button input read as HIGH:
    - I would increment a counter,
    - and use a blocking delay (this was my way of preventing back-to-back button inputs
        - Apparently, my professor did something similar in his example too
- Another method to debounce:
    - record time of when the button is previously read
    - see if 50ms has passed
    - accept another input
