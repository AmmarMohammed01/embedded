# Timer Project

ATmega328p
Used Timer/Counter1 to blink LED approximately every second (1s).

## How it was done:
- Timer/Counter1 is a 16-bit peripheral.
- The CPU frequency of ATmega328p is set to 16MHz (16,000,000).
- The Timer/Counter counts 0 to 65535 or 65536 values.
- 16000000 / 65536 = 244.141 (# of Counter overflows each second)

- An ISR runs each time the timer1 overflow interrupt vector is detected.
- A volatile overflow counter is incremented.
- Once the overflow count reaches 244, the output of PORTB5 is toggled.
