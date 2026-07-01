MCU = atmega328p
F_CPU = 16000000UL
# frequency of 16MHz

TOOLCHAIN = ~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin
CC =      $(TOOLCHAIN)/avr-gcc
OBJCOPY = $(TOOLCHAIN)/avr-objcopy

AVRDUDE_PATH = ~/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17
AVRDUDE = $(AVRDUDE_PATH)/bin/avrdude
CONF =    $(AVRDUDE_PATH)/etc/avrdude.conf

PORT = /dev/cu.usbmodem1101

#CPP stands for C Preprocessor
CPPFLAGS = -Iinclude
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
OBJFLAGS = -O ihex -R .eeprom

SRC = src/main.c src/led.c src/button.c
# OBJ = $(SRC:.c=.o)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

all: build/program.hex

build/program.elf: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# %.o: %.c # how to build any .o from corresponding .c
#	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

build/%.o: src/%.c # how to build any .o from corresponding .c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

build/program.hex: build/program.elf
	$(OBJCOPY) $(OBJFLAGS) $< $@

flash: build/program.hex
	$(AVRDUDE) -C $(CONF) -c arduino -p $(MCU) -P $(PORT) -b115200 -U flash:w:$<:i

clean:
	rm build/* # rm build/*.elf build/*.hex
