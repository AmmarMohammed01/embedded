# MSP432P401R On-Board LED Blink

**Date:** September 16, 2026
**Platform:** TI MSP432P401R
**Language:** C
**Development Environment:** Code Composer Studio (CCS)

## Overview

This is my first bare-metal GPIO exercise on the **TI MSP432P401R**.

The program configures **Port 2, Pin 2 (P2.2)** as a GPIO output and repeatedly toggles the pin to blink the MSP432 development board's on-board blue LED.

Rather than using a high-level GPIO driver, this exercise accesses the GPIO peripheral registers directly using their memory-mapped addresses.

## What This Exercise Demonstrates

* MSP432P401R GPIO configuration
* Memory-mapped peripheral registers
* Register addresses and offsets
* C pointers and pointer dereferencing
* `volatile` for hardware registers
* Bit manipulation
* GPIO direction configuration
* GPIO output control
* Peripheral function selection
* Busy-loop delays
* Watchdog timer configuration

## Hardware

* TI MSP432P401R development board
* On-board blue LED connected to **P2.2**

## GPIO Configuration

Before using P2.2 as a normal GPIO pin, the pin's peripheral function is configured through `P2SEL0` and `P2SEL1`.

```c
P2SEL1 &= ~(1 << 2);
P2SEL0 &= ~(1 << 2);
```

Clearing bit 2 in both registers selects the GPIO function for P2.2.

The direction is then configured as an output:

```c
P2DIR |= (1 << 2);
```

Finally, the output is initially driven HIGH:

```c
P2OUT |= (1 << 2);
```

## Direct Register Access

Instead of using symbolic register definitions for the GPIO registers, this program calculates their addresses manually.

```c
#define peripheral_offset 0x40004C00
#define p2out_offset 0x03
#define p2dir_offset 0x05
#define p2sel0_offset 0x0B
#define p2sel1_offset 0x0D
```

The registers are then defined by casting their addresses to pointers:

```c
#define P2OUT *((volatile char*)(peripheral_offset + p2out_offset))
#define P2DIR *((volatile char*)(peripheral_offset + p2dir_offset))
#define P2SEL0 *((volatile char*)(peripheral_offset + p2sel0_offset))
#define P2SEL1 *((volatile char*)(peripheral_offset + p2sel1_offset))
```

This demonstrates an important concept in embedded programming: **microcontroller peripherals are accessed through memory-mapped registers**.

The `volatile` qualifier tells the compiler that these memory locations represent hardware registers whose values may have effects outside normal program flow. The compiler therefore should not optimize accesses to them away or treat them like ordinary memory.

## Bit Manipulation

The program uses bitwise operations to modify individual GPIO configuration bits without changing the other bits in the register.

### Clearing a bit

```c
P2SEL1 &= ~(1 << 2);
```

`1 << 2` produces:

```text
00000100
```

Inverting it produces:

```text
11111011
```

ANDing the register with this value clears bit 2 while leaving the other bits unchanged.

### Setting a bit

```c
P2DIR |= (1 << 2);
```

ORing with `00000100` sets bit 2 while preserving the remaining bits.

### Toggling a bit

```c
P2OUT ^= (1 << 2);
```

XOR toggles bit 2:

* `0 ^ 1 = 1`
* `1 ^ 1 = 0`

Therefore, every execution of this statement changes P2.2 from HIGH to LOW or from LOW to HIGH.

## Delay

The LED is given time between each toggle using a simple busy-loop:

```c
for(i = 0; i < 500000; i++){}
```

This is a basic delay technique where the CPU continuously executes the loop until the counter reaches the specified value.

This approach is useful for learning, but it is not an accurate timing mechanism because the delay depends on the processor clock frequency, compiler optimization, and generated machine code.

Later exercises can replace this with a hardware timer.

## Program Flow

The program follows this sequence:

1. Stop the watchdog timer.
2. Configure P2.2 for GPIO operation.
3. Configure P2.2 as an output.
4. Set P2.2 HIGH.
5. Enter an infinite loop.
6. Wait using a busy-loop.
7. Toggle P2.2.
8. Repeat.

Conceptually:

```text
Start
  |
  v
Stop Watchdog
  |
  v
Configure P2.2 as GPIO
  |
  v
Configure P2.2 as Output
  |
  v
Set P2.2 HIGH
  |
  v
+-------------------+
| Busy-loop delay   |
+-------------------+
          |
          v
   Toggle P2.2
          |
          +--------> repeat
```

## Why `msp.h` Is Still Included

Although the GPIO registers are being defined manually, the program still includes:

```c
#include "msp.h"
```

This is currently used for the watchdog timer definitions:

```c
WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
```

This means the program is using a mixture of:

* TI-provided device definitions for the watchdog
* manually defined memory-mapped GPIO registers

This was intentional for learning purposes so that the underlying relationship between peripheral addresses and C code could be explored.

## Key Takeaways

This exercise introduced the basic structure of bare-metal programming on the MSP432:

* A peripheral is controlled by reading and writing specific memory addresses.
* Register offsets can be used to calculate peripheral register addresses.
* C pointers can be used to access those addresses.
* `volatile` is important when working with hardware registers.
* Bitwise operations allow individual register bits to be modified.
* GPIO pins must be configured for the appropriate peripheral function and direction before use.
* A simple busy-loop can create a delay, but hardware timers are more appropriate for accurate timing.

## Next Steps

Possible extensions of this exercise include:

* Replace the manually calculated GPIO addresses with the definitions provided by the MSP432 device header.
* Investigate the MSP432 memory map and GPIO register layout in the datasheet/user's guide.
* Create a reusable GPIO driver.
* Replace the busy-loop with a hardware timer.
* Learn how GPIO interrupts work.
* Configure multiple GPIO pins.
* Explore the relationship between GPIO pins and alternate peripheral functions.

This exercise serves as the starting point for transitioning from **bare-metal AVR programming** to **bare-metal ARM Cortex-M development** on the MSP432P4111.
