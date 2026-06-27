MCU = atmega328p
F_CPU = 16000000UL

CC = ~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-gcc
OBJCOPY = ~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-objcopy
AVRDUDE = ~/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude
CONF = ~/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf
PORT = /dev/cu.usbmodem1101

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
OBJFLAGS = -O ihex -R .eeprom

all: blink.hex

blink.elf: blink.c  # target: prereq1 prereq2
	# $(CC) $(CFLAGS) -o blink.elf blink.c
	$(CC) $(CFLAGS) -o $@ $< # the @ means target, < means prereq1

blink.hex: blink.elf
	$(OBJCOPY) $(OBJFLAGS) $< $@

flash: blink.hex
	$(AVRDUDE) -C $(CONF) -c arduino -p $(MCU) -P $(PORT) -b115200 -U flash:w:blink.hex:i

clean:
	rm *.elf *.hex
