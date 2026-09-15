## Materials
- Arduino Uno R3 board, for ATmega328p mcu
- TMP36: Analog Temperature Sensor

## Circuit
TMP36 flat side towards you:
- Left pin: Vs (2.7 to 5.5)
- Middle pin: Vout
- Right pin: GND

## Output I Got
```text
ADC: 147, 0.72 volts, 21.78'C, 71.20'F
ADC: 147, 0.72 volts, 21.78'C, 71.20'F
ADC: 163, 0.80 volts, 29.59'C, 85.26'F
ADC: 145, 0.71 volts, 20.80'C, 69.44'F
ADC: 145, 0.71 volts, 20.80'C, 69.44'F
ADC: 147, 0.72 volts, 21.78'C, 71.20'F
ADC: 145, 0.71 volts, 20.80'C, 69.44'F
```

## Other info
656 bytes before I added dtostrf and stdlib.h.
3344 bytes after adding those.
