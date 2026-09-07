MCU = atmega328p
F_CPU = 16000000UL

TOOLCHAIN = ~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin
CC =      $(TOOLCHAIN)/avr-gcc
OBJCOPY = $(TOOLCHAIN)/avr-objcopy

AVRDUDE_PATH = ~/Library/Arduino15/packages/arduino/tools/avrdude/8.0.0-arduino1/
AVRDUDE = $(AVRDUDE_PATH)/bin/avrdude
CONF =    $(AVRDUDE_PATH)/etc/avrdude.conf

PORT = /dev/cu.usbmodem1101

CPPFLAGS = -Iinclude
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
OBJFLAGS = -O ihex -R .eeprom

SRC = src/main.c src/usart.c src/helper.c src/my_i2c.c src/tmp1075_helper.c
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

all: build/program.hex

build/program.elf: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: src/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

build/program.hex: build/program.elf
	$(OBJCOPY) $(OBJFLAGS) $< $@

flash: build/program.hex
	$(AVRDUDE) -C $(CONF) -c arduino -p $(MCU) -P $(PORT) -b115200 -U flash:w:$<:i

clean:
	rm -rf build/*

my_test: test/test.c src/helper.c
	clang -g -Iinclude test/test.c src/helper.c -o build/outTest
