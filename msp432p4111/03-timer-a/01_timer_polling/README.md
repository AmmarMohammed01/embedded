# MSP432P4111 Timer_A Polling LED Blink

**Date:** September 20, 2026
**Platform:** TI MSP432P4111
**Language:** C
**Development Environment:** Code Composer Studio (CCS)

## Overview

This exercise uses the MSP432P4111's **Timer_A0 peripheral** to blink an LED at approximately 2 Hz.

Unlike the previous LED exercises, this program does not use a software busy-loop for timing. Instead, **Timer_A0 counts using SMCLK**, and the program continuously polls the timer's capture/compare interrupt flag (`CCIFG`).

When the timer reaches `CCR0`, the flag is set. The program detects the flag, clears it, and toggles the LED.

This exercise was also an opportunity to investigate the MSP432P4111 device header, the clock system, Timer_A register definitions, timer dividers, and how vendor-provided register macros are represented.

## What This Exercise Demonstrates

* Timer_A peripheral configuration
* 16-bit timer operation
* SMCLK as a timer clock source
* Timer input division
* Timer input divider expansion
* Capture/compare registers
* Timer polling
* Timer flags
* Bit manipulation
* Memory-mapped peripheral registers
* MSP432P4111 device header investigation
* Debugging peripheral configuration
* Calculating timer periods from clock frequencies

## Hardware

* TI MSP432P4111 development board
* LED connected to **P1.0**

## GPIO Configuration

P1.0 is configured as a GPIO output:

```c
P1->SEL0 &= ~BIT0;
P1->SEL1 &= ~BIT0;
P1->DIR |= BIT0;
P1->OUT |= BIT0;
```

The pin is initially driven HIGH.

The LED is toggled whenever Timer_A0 reaches its compare value.

---

# Timer_A Configuration

Timer_A0 is configured with SMCLK as its clock source and operates in **up mode**.

```c
TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2
              | TIMER_A_CTL_MC_1
              | TIMER_A_CTL_ID__8;
```

The configuration is:

| Setting           |   Value | Purpose                       |
| ----------------- | ------: | ----------------------------- |
| Clock source      |   SMCLK | Timer clock                   |
| Timer mode        | Up mode | Counts from 0 to `CCR0`       |
| Input divider     |    `/8` | Reduces timer clock frequency |
| Expansion divider |    `/8` | Further reduces timer clock   |
| Effective divider |   `/64` | Combined division             |

The timer is therefore clocked at:

```text
Timer frequency = SMCLK / 8 / 8
                = SMCLK / 64
```

---

# Understanding SMCLK

One of the main parts of the investigation was determining the actual frequency of SMCLK.

The MSP432P4111 device header defines the SMCLK selection bits for Timer_A, including:

```c
TIMER_A_CTL_TASSEL_2
```

The MSP432 clock system documentation was then used to determine where SMCLK gets its clock source.

The clock system uses a multiplexer to select the SMCLK source. The default `SELS` setting selects the DCO clock source.

The project's system configuration sets the DCO to the range containing **3 MHz**, resulting in a 3 MHz system clock configuration for this project.

Therefore:

```text
SMCLK = 3,000,000 Hz
```

The Timer_A clock is then divided by the two `/8` dividers:

```text
3,000,000 / 8 / 8
= 46,875 Hz
```

So Timer_A0 receives a clock of approximately:

```text
46.875 kHz
```

---

# Timer Divider Investigation

The timer is a 16-bit counter, so its maximum count is:

```text
65535
```

Initially, calculating a 250 ms period directly from a 3 MHz clock gives:

```text
ticks = (0.250 s × 3,000,000 Hz) - 1
      = 749,999
```

This cannot fit into a 16-bit timer.

## Timer Input Divider

Timer_A provides an input divider that can divide the clock by up to 8.

Using `/8`:

```text
3,000,000 / 8
= 375,000 Hz
```

A 250 ms period would then require:

```text
ticks = (0.250 × 375,000) - 1
      = 93,749
```

This still exceeds the 16-bit maximum of 65,535.

## Input Divider Expansion

Timer_A also provides an **input divider expansion** through the `TAxEX0` register.

The expansion divider can provide another division factor of up to `/8`.

Using both:

```text
Input divider       = /8
Input expansion     = /8

Total division      = /64
```

The resulting timer frequency is:

```text
3,000,000 / 64
= 46,875 Hz
```

Now the required count for approximately 250 ms is:

```text
ticks = (0.250 × 46,875) - 1
      = 11,717.75
```

The program uses:

```c
TIMER_A0->CCR[0] = 23436;
```

which results in a timer interval of approximately 500 ms.

I decided to switch from 250ms to 500ms so that the LED would blink slower.

Because the LED toggles once per timer interval, the output is approximately:

```text
500 ms HIGH
500 ms LOW
```

with a complete period of approximately:

```text
1000 ms
```

and therefore approximately:

```text
1 Hz
```

---

# Capture/Compare Register

The timer's capture/compare register is configured with:

```c
TIMER_A0->CCR[0] = 23436;
```

Timer_A is operating in up mode, so the counter repeatedly counts:

```text
0 → 1 → 2 → ... → 23436 → 0 → ...
```

When the timer reaches the configured compare value, the corresponding capture/compare flag is set.

The timer therefore provides a repeating timing event without requiring the CPU to execute a software delay loop.

---

# Polling Instead of Interrupts

Although the timer generates a flag associated with a capture/compare event, this program does **not** use a CPU interrupt.

Instead, the program continuously checks the flag:

```c
if(TIMER_A0->CCTL[0] & TIMER_A_CCTLN_CCIFG)
```

This is called **polling**.

When the flag is set, the program clears it:

```c
TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
```

and toggles the LED:

```c
P1->OUT ^= BIT0;
```

The overall process is:

```text
Timer counts
     |
     v
Timer reaches CCR0
     |
     v
CCIFG becomes set
     |
     v
CPU polls CCTL[0]
     |
     v
CCIFG detected
     |
     v
Clear CCIFG
     |
     v
Toggle LED
     |
     v
Timer continues counting
```

The important distinction is that **the timer is generating the timing event, but the CPU is still responsible for continuously checking for it**.

---

# Debugging the Timer Configuration

The timer initially did not produce the expected LED behavior, so I used the debugger to inspect the Timer_A registers.

The observed `TACTL` configuration was:

```text
TASSEL = 01  → ACLK
ID     = 00  → /1
MC     = 00  → Stop
```

This did not match the configuration I intended.

## The Problem

The initial code attempted to shift the Timer_A macros manually:

```c
TIMER_A0->CTL =
    (TIMER_A_CTL_TASSEL_2 << TIMER_A_CTL_SSEL_OFS)
    | (TIMER_A_CTL_MC_1 << TIMER_A_CTL_MC_OFS)
    | (TIMER_A_CTL_ID__8 << TIMER_A_CTL_ID_OFS);
```

The mistake was assuming that these macros contained unshifted values that needed to be moved into position.

The MSP432 device header's Timer_A macros already encode their positions within the register.

For example:

```c
TIMER_A_CTL_TASSEL_2
```

already represents the appropriate bit pattern for the SMCLK selection field.

Likewise:

```c
TIMER_A_CTL_MC_1
```

already represents the appropriate value in the mode-control field.

Therefore, adding the offsets again moved the fields to incorrect positions.

## Correct Configuration

The corrected code is:

```c
TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2
              | TIMER_A_CTL_MC_1
              | TIMER_A_CTL_ID__8;
```

This was an important lesson about using vendor-provided register macros:

> **Before shifting a register macro, inspect its definition to determine whether the bit position is already encoded.**

This is especially important when working with vendor device headers because macros may represent either:

* a raw field value that still needs shifting, or
* a fully positioned register value that can be ORed directly into the register.

---

# Investigating the MSP432 Device Header

A significant part of this exercise involved reading the MSP432P4111 device header instead of treating the peripheral definitions as a black box.

Relevant sections investigated included:

### Timer_A structure

The `Timer_A_Type` structure contains the Timer_A registers, including the capture/compare register array:

```c
CCR[5]
```

This makes code such as:

```c
TIMER_A0->CCR[0]
```

possible.

### Timer_A peripheral declaration

The device header declares the Timer_A peripherals using pointers to the Timer_A structure.

This allows code such as:

```c
TIMER_A0->CTL
TIMER_A0->CCTL[0]
TIMER_A0->CCR[0]
TIMER_A0->EX0
```

to directly access the corresponding memory-mapped registers.

### Clock System

I also investigated the `CS_Type` structure and the clock-system registers to understand where SMCLK originates.

This was necessary because timer calculations are only useful if the actual timer input frequency is known.

---

# Timing Calculation

The final timer configuration is:

```text
DCO / SMCLK       = 3,000,000 Hz

Timer divider:
    ID            = /8
    IDEX          = /8

Effective timer clock:
    3,000,000 / 64
    = 46,875 Hz
```

With:

```text
CCR0 = 23,436
```

the timer period is approximately:

```text
(23,436 + 1) / 46,875
≈ 0.5 seconds
```

Therefore the LED toggles approximately every 500 ms.

```text
HIGH ≈ 500 ms
LOW  ≈ 500 ms

Complete period ≈ 1000 ms
Frequency ≈ 1 Hz
```

<!-- **toggle interval** and **output period** was an important part of the timing calculation. -->

---

# Busy-Loop vs Timer Polling

This exercise replaces the previous software delay:

```c
for(i = 0; i < 500000; i++) {
}
```

with a hardware timer.

### Busy-loop

```text
CPU
 |
 +--> execute instructions
 |
 +--> execute instructions
 |
 +--> execute instructions
 |
 +--> toggle GPIO
```

The CPU is occupied doing nothing useful while waiting.

### Timer polling

```text
Timer ───────────────> generates timing event
                         |
CPU --> repeatedly checks flag
                         |
                         +--> toggle GPIO
```

The timer provides a hardware-based time reference, although the CPU still spends its time polling the flag.

The next step beyond polling is to use a **Timer_A interrupt**, allowing the CPU to perform other work while waiting for the timer event.

---

# Key Learning Points

This exercise introduced several important embedded-systems concepts:

* Hardware timers can replace software delay loops.
* Timer_A can use SMCLK as its clock source.
* Timer input dividers allow a high-frequency clock to be reduced.
* Timer_A's expansion divider provides an additional division stage.
* A 16-bit timer places constraints on the maximum achievable period.
* `CCR0` determines the terminal count when using Timer_A up mode.
* Hardware events can be detected by polling status flags.
* Polling is different from using a CPU interrupt.
* Vendor register macros may already contain their required bit positions.
* Debugger register views are useful for diagnosing peripheral configuration problems.
* Understanding the clock tree is necessary when calculating timer periods.
* Reading the device header and technical reference manual is an important embedded development skill.

## Research Process

This exercise involved consulting several sources within the TI development environment:

* `msp432p4111.h`
* `system_msp432p4111.c`
* MSP432P4111 Technical Reference Manual
* MSP432P4111 datasheet

Rather than relying only on example code, I traced the definitions from the peripheral structure and register macros into the device documentation to understand what the code was actually configuring.

## Next Steps

The natural progression from this exercise is:

1. Learn how Timer_A interrupts work.
2. Configure `CCIE` for the capture/compare channel.
3. Enable the appropriate NVIC interrupt.
4. Move the LED toggle from the polling loop into an ISR.
5. Compare polling and interrupt-driven implementations.
6. Learn how to configure Timer_A for other timing intervals.
7. Investigate continuous mode and compare it with up mode.
8. Use a timer for tasks more useful than simply blinking an LED.
