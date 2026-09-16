# 2026-09-16: First MSP432P4111 Project

## Creating a New CCS Project
CCS Code Composer Studio already installed.

Create new CCS project.

Target: MSP432 Family > MSP432P4111
Connections: Texas Instruments XDS110 USB Debug Probe [Default]
Project Name: 01-first-project
Compiler Version: TI v.20.2.5.LTS

Project type and toolchain: executable eabi (ELF), device edianness little.

## How to Compile and Upload CCS Project?
Options I see at the top:
- (Bug) Debug
- (Folder w/ Code) Flash
- (Hammer) Build
- (Magnifying Glass) Energy Trace

I chose the hammer first, to build.
- It ran a bunch of commands shown in console
- Then it said "Build Finished"

I clicked flash next.
- Bottom right, it showed percentage of flash progress.
- Some window appeared, I think I saw the word "debug-"

LED01 red was flashing, then it stopped.

LED02 green is always on, even after flashing complete.
- Probably used to just show MCU is on.

## Using the Debugger
Now I will click "debug" button.

At the top, I see debug specific buttons:
- resume
- suspend
- terminate
- step into
- step over
- step return

My current main.c:
```C
#include "msp.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; //stop watchdog timer [A BREAKPOINT WAS AUTOMATICALLY SET HERE]
}
```

Other things I see. Many different sub-windows or panes in debug mode:
- debug at top left
- variables, expressions, registers at top right
- code in the middle
- console at the bottom

There was a breakpoint at the WDT line. I clicked resume button.
Took me to exit.c

I clicked suspend.
Shows a line
```C
for(;;); /* SPINS FOREVER */
```

Now I click terminate --> I exit debug view, and I see my workspace setup again: folders to the left and code to the right.
