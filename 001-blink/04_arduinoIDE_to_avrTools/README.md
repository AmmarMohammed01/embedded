# Arduino IDE to AVR Tools, Blink Example
## Summary
In this project, I was able to swtich from Arduino IDE to AVR Tools<br>
to compile and upload embedded software for Arduino Uno R3 (ATmega328p).

I used tools such as avr-gcc, avr-objcopy, & avrdude to compile and flash the code.

I also used avr-objdump and avr-size to examine the .elf file.

Finally I created a Makefile to automate the process. NOTE: Makefile usage instructions below.

## Overview
C source<br>
   \\/<br>
avr-gcc<br>
   \\/<br>
blink.elf<br>
   \\/<br>
avr-objcopy<br>
   \\/<br>
blink.hex<br>
   \\/<br>
avrdude<br>
   \\/<br>
ATmega328P

## Process
blink.c
```
1. I converted/renamed my previous blink.ino to blink.c
```

commands.txt<br>
```
2. I started using AVR commands (avr-gcc, avr-objcopy)
3. I used "avrdude" to flash the microcontroller with the .hex file
```

Makefile
```
4. I made a Makefile and learned about \$@ and \$< shorthands
```

## Makefile Usage
```bash
make # generates blink.elf and blink.hex files

make flash # uploads blink.hex to microcontroller when connected

make clean # removes .elf and .hex files
```