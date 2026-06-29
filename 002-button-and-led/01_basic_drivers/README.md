# Project 002 - Button & LED
## About
This project explores how to receive input via GPIO pins without using the Arduino libraries.

## Project Structure:
src/
- Contains source code (*.c files)

include/
- Contains header files (*.h files)

build/
- Contains object files (*.o files)
- Useful in development if changes are only made to some source code files while others remain unchanged, which can decrease build time as projects get larger

Makefile
- Contains compiler commands and setting to run and clean work environment

## Notes
Trying to use avr/io header file for the first time.
Found at: ~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/avr/include/avr/io.h
io.h includes the iom328p.h header file if the symbol ```__AVR_ATmega328p__``` is defined.

I am trying to understand how to use the avr/io header.
Looking at iom328p.h,
```C
#define PINB _SFR_IO8(0x03)
...
#define DDRB _SFR_IO8(0x04)
...
#define PORTB _SFR_IO8(0x05)
#define PORTB0 0
#define PORTB1 1
#define PORTB2 2
...
```
the hex number matches the address in the datasheet when refering to the I/O memory space registers (before offset is added).

Another thing I found io.h includes sfr_defs.h
_SFR_IO8 is defined as a macro that adds the io address passed to the offset of 0x20 (same as in datasheet).

## Makefile Results
```bash
>> ls */
build/:

include/:
led.h

src/:
led.c  main.c

>> make
~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-gcc -Iinclude -mmcu=atmega328p -DF_CPU=16000000UL -Os -c src/main.c -o build/main.o
~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-gcc -Iinclude -mmcu=atmega328p -DF_CPU=16000000UL -Os -c src/led.c -o build/led.o
~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os build/main.o build/led.o -o build/program.elf
~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-objcopy -O ihex -R .eeprom build/program.elf build/program.hex

>> ls */
build/:
led.o       main.o      program.elf program.hex

include/:
led.h

src/:
led.c  main.c

>> make clean
rm build/*.elf build/*.hex

>> ls */
build/:
led.o  main.o

include/:
led.h

src/:
led.c  main.c

>> make
~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os build/main.o build/led.o -o build/program.elf
~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-objcopy -O ihex -R .eeprom build/program.elf build/program.hex

>> ls */
build/:
led.o       main.o      program.elf program.hex

include/:
led.h

src/:
led.c  main.c
```
