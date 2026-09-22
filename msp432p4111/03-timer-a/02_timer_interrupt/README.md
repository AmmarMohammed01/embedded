# MSP432P4111 Timer_A Interrupt-Driven LED Blink

**Date:** September 21, 2026
**Platform:** TI MSP432P4111
**CPU:** ARM Cortex-M4F
**Language:** C
**Development Environment:** Code Composer Studio (CCS)

## Overview

This exercise builds on the previous Timer_A polling exercise by replacing **polling** with a **hardware interrupt**.

Timer_A0 is configured to generate a capture/compare event approximately every 500 ms. Instead of continuously checking the timer's `CCIFG` flag in the main loop, the timer interrupt is enabled and the ARM Cortex-M4F's **Nested Vectored Interrupt Controller (NVIC)** is configured to route the interrupt to an interrupt service routine (ISR).

When the timer reaches `CCR0`:

1. Timer_A sets `CCIFG`.
2. The Timer_A interrupt request is generated because `CCIE` is enabled.
3. The NVIC detects the interrupt.
4. The CPU enters `TA0_0_IRQHandler()`.
5. The ISR clears the flag and toggles P1.0.
6. Execution returns from the ISR.

The `while(1)` loop no longer needs to perform the timing work.

---

# What This Exercise Demonstrates

* Timer_A interrupts
* Capture/compare interrupt flags
* `CCIE` interrupt enable
* ARM Cortex-M4F NVIC
* IRQ numbers
* Interrupt vector tables
* Interrupt service routines
* `NVIC_EnableIRQ()`
* `__enable_irq()`
* Vendor startup code
* Device header investigation
* Timer_A compare mode
* 16-bit timer operation
* Hardware-based timing
* Difference between polling and interrupts
* Debugging and tracing interrupt configuration

---

# Hardware

* TI MSP432P4111 development board
* LED connected to **P1.0**

The LED is initially driven HIGH and is toggled by the Timer_A interrupt.

---

# GPIO Configuration

P1.0 is configured as a GPIO output:

```c
P1->SEL0 &= ~BIT0;
P1->SEL1 &= ~BIT0;
P1->DIR |= BIT0;
P1->OUT |= BIT0;
```

The important point here is that `BIT0` already represents bit 0:

```text
BIT0 = 0x0001 = 1 << 0
```

Therefore:

```c
~BIT0
```

is used to clear bit 0.

An expression such as:

```c
1 << BIT0
```

would be incorrect for this purpose because `BIT0` has the value `1`, so it would shift by one position rather than representing the bit mask itself.

---

# Timer_A Configuration

Timer_A0 is configured using SMCLK:

```c
TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2
              | TIMER_A_CTL_MC_1
              | TIMER_A_CTL_ID__8;
```

The configuration is:

| Setting                 | Configuration |
| ----------------------- | ------------- |
| Clock source            | SMCLK         |
| Timer mode              | Up mode       |
| Input divider           | `/8`          |
| Input expansion divider | `/8`          |
| Effective divider       | `/64`         |
| `CCR0`                  | `23436`       |

The expansion divider is configured with:

```c
TIMER_A0->EX0 = TIMER_A_EX0_IDEX__8;
```

With SMCLK at approximately 3 MHz:

```text
3,000,000 Hz / 8 / 8
= 46,875 Hz
```

The timer therefore receives approximately 46,875 clock ticks per second.

---

# Timer Period

The compare register is configured as:

```c
TIMER_A0->CCR[0] = 23436;
```

In Timer_A up mode, the timer counts from zero through `CCR0`.

Therefore, the number of timer ticks between compare events is:

```text
CCR0 + 1
= 23,437 ticks
```

The approximate interval is:

```text
23,437 / 46,875
≈ 0.5 seconds
```

The LED toggles approximately every 500 ms.

Because each toggle changes the LED state, the LED remains HIGH for approximately 500 ms and LOW for approximately 500 ms.

A complete HIGH → LOW → HIGH cycle takes approximately 1 second, corresponding to a blink frequency of approximately 1 Hz.

```text
HIGH ≈ 500 ms
LOW  ≈ 500 ms

Complete period ≈ 1000 ms
Frequency ≈ 1 Hz
```

---

# Enabling the Timer Interrupt

The capture/compare interrupt is enabled through the `CCIE` bit:

```c
TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;
```

`CCIE` stands for **Capture/Compare Interrupt Enable**.

This is different from `CCIFG`, which is the **Capture/Compare Interrupt Flag**.

The relationship is:

```text
Timer reaches CCR0
        |
        v
     CCIFG set
        |
        v
CCIE is enabled?
        |
       yes
        |
        v
 Interrupt request
        |
        v
      NVIC
```

`CCIE` allows the capture/compare event to generate an interrupt request.

---

# CCIFG vs TAIFG

One part of this investigation was understanding the difference between `CCIFG` and `TAIFG`.

## CCIFG

`CCIFG` is a capture/compare interrupt flag.

In compare mode, Timer_A compares the current timer value against the value stored in `TAxCCRn`.

When they match:

```text
TAxR == TAxCCRn
```

the corresponding `CCIFG` is set.

For this project:

```text
TA0R == TA0CCR0
```

causes the channel 0 `CCIFG` to be set.

## TAIFG

`TAIFG` is associated with the timer itself overflowing.

This is different from the channel-specific capture/compare event.

Conceptually:

```text
CCIFG
  |
  +--> Timer reaches a channel's CCR value


TAIFG
  |
  +--> Timer reaches its overflow condition
```

Understanding this distinction helped clarify why this project uses the Timer_A channel 0 interrupt rather than the timer overflow interrupt.

---

# NVIC

The MSP432 uses an ARM Cortex-M4F processor.

The Cortex-M processor provides an interrupt controller called the **Nested Vectored Interrupt Controller (NVIC)**.

The NVIC handles interrupt requests from peripherals and determines which interrupt should be serviced.

The Timer_A0 channel 0 interrupt is represented by:

```c
TA0_0_IRQn
```

The MSP432P4111 device header defines:

```text
TA0_0_IRQn = 8
```

The interrupt therefore corresponds to IRQ number 8.

The program enables it with:

```c
NVIC_EnableIRQ(TA0_0_IRQn);
```

`NVIC_EnableIRQ()` is provided through the ARM CMSIS definitions.

---

# What Does IRQ Mean?

IRQ means:

**Interrupt Request**

An IRQ represents a request from a peripheral or other hardware source for the CPU to service an event.

In this example:

```text
Timer_A0
   |
   | interrupt request
   v
 NVIC
   |
   v
CPU
   |
   v
TA0_0_IRQHandler()
```

---

# Interrupt Vector Table

One of the most useful discoveries during this exercise was understanding where the interrupt handler actually comes from.

The code defines:

```c
void TA0_0_IRQHandler(void)
{
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    P1->OUT ^= BIT0;
}
```

There is no function call to `TA0_0_IRQHandler()` in `main()`.

Instead, the **interrupt vector table** associates the Timer_A0 channel 0 IRQ with this handler.

The MSP432 startup file contains the vector table and declarations for interrupt handlers.

The startup code uses `extern` declarations for handlers that are implemented elsewhere.

Conceptually:

```text
startup_msp432p4111_ccs.c
        |
        | vector table
        v
TA0_0_IRQHandler
        ^
        |
        | implementation
        |
main.c
```

This means the linker connects the handler implementation in `main.c` to the corresponding entry in the startup vector table.

---

# `extern` in the Startup Code

The startup file contains declarations for interrupt handlers that may be implemented in other source files.

The `extern` keyword tells the compiler that the function exists elsewhere.

For example, conceptually:

```c
extern void TA0_0_IRQHandler(void);
```

The actual implementation can then exist in another source file:

```c
void TA0_0_IRQHandler(void)
{
    // ISR implementation
}
```

If an interrupt handler is not implemented by the application, the startup code provides a default handler.

The default handler is typically an infinite loop, so an unexpected interrupt can cause the processor to remain there.

This helped explain why an ISR does not need to be called explicitly from `main()`.

---

# Interrupt Handler

The Timer_A0 channel 0 ISR is:

```c
void TA0_0_IRQHandler(void)
{
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    P1->OUT ^= BIT0;
}
```

When the interrupt occurs, the CPU automatically enters this function.

The ISR performs two operations.

## 1. Clear the Interrupt Flag

```c
TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
```

This clears `CCIFG`.

Clearing the flag prevents the same pending event from continuously retriggering the interrupt.

The SDK example I investigated also explicitly clears the flag inside the ISR, which helped confirm that it should be handled by the application code.

## 2. Toggle the LED

```c
P1->OUT ^= BIT0;
```

This changes the state of P1.0.

Therefore, every timer interrupt causes one LED transition.

---

# Why Use an Interrupt Instead of Polling?

The previous exercise used:

```c
while(1) {
    if(TIMER_A0->CCTL[0] & TIMER_A_CCTLN_CCIFG) {
        TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
        P1->OUT ^= BIT0;
    }
}
```

The CPU continuously checked the timer flag.

That is **polling**.

The new implementation instead uses:

```c
while(1) {
}
```

and allows the timer to interrupt the CPU.

### Polling

```text
CPU
 |
 +--> check flag
 |
 +--> check flag
 |
 +--> check flag
 |
 +--> check flag
 |
 +--> event detected
       |
       v
    toggle LED
```

### Interrupt

```text
CPU
 |
 +--> execute main program
 |
 +--> execute main program
 |
 +--> ...
 |
 |       Timer event
 |           |
 |           v
 |          NVIC
 |           |
 |           v
 |          ISR
 |           |
 |           v
 |       toggle LED
 |           |
 +<----------+
```

The interrupt-based approach allows the main program to perform other work while the timer runs independently.

This is a fundamental pattern in embedded firmware.

---

# `__enable_irq()`

The code contains:

```c
NVIC_EnableIRQ(TA0_0_IRQn);
__enable_irq();
```

These perform two different jobs.

### `NVIC_EnableIRQ()`

This enables the specific Timer_A0 interrupt in the NVIC.

```c
NVIC_EnableIRQ(TA0_0_IRQn);
```

### `__enable_irq()`

This enables interrupts at the ARM Cortex-M CPU level.

```c
__enable_irq();
```

The CMSIS headers provide this as an ARM core function.

---

# Why Did It Work Without `__enable_irq()`?

During this experiment, the interrupt worked even when:

```c
__enable_irq();
```

was removed.

This led to an investigation of the startup code and processor initialization.

The important distinction is that there are multiple levels involved in interrupt operation:

```text
Peripheral
   |
   | CCIE
   v
NVIC
   |
   | NVIC_EnableIRQ()
   v
CPU interrupt enable state
   |
   | __enable_irq()
   v
Interrupt execution
```

If interrupts have already been globally enabled by the time `main()` begins, explicitly calling `__enable_irq()` may not be necessary for this particular program.

However, explicitly enabling interrupts makes the intent clear and avoids depending on assumptions about the processor's current interrupt state.

---

# Investigating CMSIS

I traced the definitions of the interrupt-related functions through the ARM CMSIS headers.

The investigation included:

* `cmsis_ccs.h`
* `cmsis_gcc.h`
* `core_cm4.h`

The headers show that `__enable_irq()` is a core ARM/CMSIS function and ultimately corresponds to enabling interrupts at the processor level.

`core_cm4.h` also defines the `NVIC_Type` structure and NVIC-related functions.

This demonstrated that not every useful embedded definition comes directly from the MSP432 device header. Some functionality comes from the **ARM CMSIS layer** provided for Cortex-M processors.

---

# Capture Mode vs Compare Mode

Another concept investigated during this exercise was the difference between Timer_A capture and compare modes.

## Capture Mode

In capture mode, the timer records the current timer value when an external event occurs.

Conceptually:

```text
External event
      |
      v
   TAxR value
      |
      v
   TAxCCRn
```

This can be used to measure the timing of external signals.

## Compare Mode

This project uses compare mode.

The application places a value in `TAxCCR0`:

```c
TIMER_A0->CCR[0] = 23436;
```

The timer continuously compares its current count against that value.

When:

```text
TA0R == TA0CCR0
```

the capture/compare flag is set.

For this project, that event is what generates the timer interrupt.

---

# Debugging and Research Process

A significant part of this exercise was understanding how the various layers connect:

```text
Timer_A peripheral
        |
        v
Timer_A register definitions
        |
        v
CCIFG / CCIE
        |
        v
Timer interrupt request
        |
        v
NVIC
        |
        v
IRQ number
        |
        v
Interrupt vector table
        |
        v
TA0_0_IRQHandler()
```

I used the following resources during the investigation:

* `msp432p4111.h`
* `startup_msp432p4111_ccs.c`
* `system_msp432p4111.c`
* ARM CMSIS headers
* MSP432P4111 Technical Reference Manual
* MSP432P4111 SDK example code

I also examined the SDK's register-level Timer_A interrupt example to compare the implementation against my own code.

---

# Key Learning Points

This exercise represents the transition from **polling-based firmware to interrupt-driven firmware**.

Important concepts learned:

* A timer can generate hardware interrupts without the CPU constantly polling it.
* `CCIFG` indicates that a capture/compare event occurred.
* `CCIE` enables the capture/compare interrupt.
* `TAIFG` represents a timer overflow event and is distinct from `CCIFG`.
* The NVIC handles interrupts on the Cortex-M4F.
* Each interrupt source has an IRQ number.
* `TA0_0_IRQn` corresponds to Timer_A0 channel 0.
* `NVIC_EnableIRQ()` enables an individual interrupt in the NVIC.
* `__enable_irq()` enables interrupts at the CPU level.
* The interrupt vector table determines which function executes for a given IRQ.
* An ISR does not need to be explicitly called from `main()`.
* Startup code connects interrupt vector entries to handler functions.
* `extern` allows the startup code to reference handlers implemented in another source file.
* Capture mode records timer values in response to events.
* Compare mode generates an event when the timer reaches a configured value.
* Hardware timers and interrupts are fundamental building blocks for non-blocking embedded firmware.

---

# Polling to Interrupt Progression

This exercise represents the progression:

```text
Exercise 1
Software busy-loop
        |
        v
Exercise 2
Timer + polling
        |
        v
Exercise 3
Timer + interrupt
```

The CPU's responsibility decreases at each step.

### Busy-loop

The CPU creates the timing itself.

### Timer polling

The hardware creates the timing event, but the CPU constantly checks for it.

### Timer interrupt

The hardware creates the timing event and notifies the CPU only when the event occurs.

This progression is an important foundation for building more complex embedded firmware.

---

# Next Steps

The next logical topics to explore are:

* Timer_A interrupt priorities
* NVIC interrupt priority configuration
* Multiple interrupt sources
* GPIO interrupts
* Interrupt latency
* ISR best practices
* Avoiding lengthy work inside ISRs
* `volatile` variables shared between ISRs and main code
* Critical sections
* Nested interrupts
* Using timers to schedule multiple periodic tasks
* Low-power modes and waking the MSP432 from an interrupt
