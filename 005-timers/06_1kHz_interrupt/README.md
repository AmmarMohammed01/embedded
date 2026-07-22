# Project #005 Timers: 1kHz Interrupt

## About

## References
ATmega328p Datasheet
- 8.12 System Clock and Clock Options: Register Description

## Calculations

16MHz CPU clock
1kHz = 1,000Hz

16,000,000 Hz / x = 1,000 Hz
x = 16,000,000 / 1,000
x = 16,000

There is not a 16,000 prescaler.

Prescale of 1024
16,000,000 Hz / 1024 = 15625 Hz

The calculation above is the slowest speed the clock can be set to when CPU frequency is 16MHz.

A 1kHz signal is still acheiveable?
Just use a compare match that triggers when current clock time matches output compare register value of 1kHz?
- After more thought, this is not the method.

Hz, a.k.a. Hertz, stands for "cycles per second."

Hence, 15,625Hz is
```
15,625 cycles   1 cycle
------------- x -------------
1 second        ? seconds

? = x

x = 1 / 15625
x = 0.000064s = 64 * 10^-6 seconds
x = 64us or microseconds
```

The above means if the output compare matches the counter at 1000, it means 1000 counts at the speed of 15,625Hz.
It means 1000 cycles in 64 milliseconds.

I need 1kHz, which is:
```
1kHz = 1*10^3 Hz = 1000Hz
1000 cycles   1 cycle
----------- = -----------
1 second      y seconds

y = 1 / 10^3 = 10^-3 = 1 ms
```
1kHz is 1000 cycles in 1 second
15,625Hz gives 1000 cycles in 64 milliseconds.

### Internal Clocks
Another plan, see if the ATmega328p can be set to a lower CPU frequency.

8.2.1 Default Clock Source
- "Device shipped with an internal RC oscillator at 8.0MHz and with the fuse CKDIV8 programmed, resulting in 1.0MHz system clock."

### Solution

I was too determined to have a 1000 cycles occur to have a 1kHz interrupt.

But the main idea of 1kHz is 1 cycle every 1ms. Remember cycle is not equal to Hz.

So this could be a solution:
```
prescaler of 8
16,000,000Hz / 8 = 2,000,000Hz

2,000,000Hz / x = 1000Hz or 1 cycle per 1ms

What is the unit of x?

x = 2,000,000Hz / 1,000Hz
2,000,000 cycles   1,000 cycles   2,000,000 cycles   1 second       2,000,000 cycles
---------------- / ------------ = ---------------- * ------------ = ---------------- = 2,000 (sets of 1,000 cycles? Or just a scaler.)
1 second           1 second       1 second           1,000 cycles   1,000     cycles

x = 2000

Meaning of 2,000,000Hz:
2,000,000 cycles   1 cycle
---------------- = ---------
1 second           y seconds

y = 1 / (2 * 10^6) = 0.5 * 10^-6 = 5 * 10^-7 = 500 nanoseconds

2MHz means 1 cycle per 500 nanoseconds.

So to get an interrupt at 1 millisecond, I need to ask: how many cycles occur in 2MHz for 1ms?

500ns * z = 1ms
(5 * 10^-7) * z = 1 * 10^-3
z = (10^-3) / (5 * 10^-7)
z = 10^4 / 5 = 10,000 / 5 = 2,000 (got this scaler or factor again)

1 cycle * z = # of cycles in 1ms for 2MHz
1 cycle * 2000 = 2000 cycles
```

## Steps

Using volatile uint8_t for counter.


