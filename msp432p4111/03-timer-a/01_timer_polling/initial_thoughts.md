# Timer A

## References
- TRM Page 13 TOC, Timer_A's sections
- TRM Page 782-802, Timer_A
    - operation
        - start the timer
        - mode control
        - capture/compare blocks
        - output unit
        - interrupts
    - register info

    - p. 784 Timer_A Block Diagram

## Questions
- What register starts/stops the timer and selects its clock source
    - TASSEL (p. 785): select clock source
- What register determines the timer's count limit in up mode
- What register tells us that the timer has reached the limit

## About
- 16-bit timer counter
- used for capture/compares (7 registers)
- pwm outputs
- interval timing
- interrupts on overflow conditions for capture/compare


