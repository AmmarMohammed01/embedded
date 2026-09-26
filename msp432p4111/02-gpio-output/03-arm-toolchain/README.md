```text
Installed simplelink_msp432p4_sdk_3_40_01_02

/Applications/ti has 
    simplelink_msp432p4_sdk_3_40_01_02
    xdctools_3_60_02_34_core

Installed arm-none-eabi-gcc using Homebrew

Homebrew 6.0.20
arm-none-eabi-gcc (GCC) 16.2.0

/Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/inc/msp.h
```

```zsh
arm-none-eabi-gcc \
    -mcpu=cortex-m4 \
    -mthumb \
    -I/Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/inc \
    -c main.c \
    -o main.o
```

```text
In file included from
main.c:1
:
/Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/inc/msp.h:76:2:
error:
#error "Failed to match a default include file" 76 | #
error
"Failed to match a default include file" |
^~~~~
main.c:
In function '
main
':
main.c:4:9:
error:
'
WDT_A
' undeclared (first use in this function) 4 |
WDT_A
->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer |
^~~~~
main.c:4:9:
note:
each undeclared identifier is reported only once for each function it appears in
main.c:4:22:
error:
'
WDT_A_CTL_PW
' undeclared (first use in this function) 4 | WDT_A->CTL =
WDT_A_CTL_PW
| WDT_A_CTL_HOLD; // stop watchdog timer |
^~~~~~~~~~~~
main.c:4:37:
error:
'
WDT_A_CTL_HOLD
' undeclared (first use in this function) 4 | WDT_A->CTL = WDT_A_CTL_PW |
WDT_A_CTL_HOLD
; // stop watchdog timer |
^~~~~~~~~~~~~~
main.c:6:9:
error:
'
P2
' undeclared (first use in this function) 6 |
P2
->SEL0 &= ~(1 << 1); P2->SEL1 &= ~(1 << 1); //set p2.1 port function as gpio |
```

```zsh
arm-none-eabi-gcc \
-mcpu=cortex-m4 \
-mthumb \
-I/Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/inc \
-c main.c \
-o main.o \
-D "__MSP432P4111__"
```

```text
In file included from
/Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/inc/msp432p4111.h:56
, from
/Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/inc/msp.h:64
, from
main.c:1
:
/opt/homebrew/Cellar/arm-none-eabi-gcc/16.2.0/lib/gcc/arm-none-eabi/16.2.0/include/stdint.h:11:16:
fatal error:
stdint.h: No such file or directory 11 | # include_next
<stdint.h>
   |
```

One thing I have noticed, there are different folders for different "build" tools:
- ccs <-- what I primarily use
- gcc <-- what I want to try
- keil
- iar

Important to MSP432P4111:
- /Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/inc/msp432p4111.h (msp432 header)
- /Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/inc/system_msp432p4111.h (system)
- /Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/startup_system_files/system_msp432p4111.c (system)
- /Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/startup_system_files/gcc/startup_msp432p4111_gcc.c (startup)
- /Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/startup_system_files/gcc/startup_msp432p4111_gcc.c (startup)
- /Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/linker_files/gcc/msp432p4111.lds (linker)

/Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/grlib/lib/gcc/m4f/

...

- /Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/examples/nortos/MSP_EXP432P4111/registerLevel/msp432p411x_1/gcc/makefile
- /Applications/ti/simplelink_msp432p4_sdk_3_40_01_02/imports.mak

It seems that there is a ccs compiler and a gcc compiler.
The gcc compiler needed is ```gcc-arm-none-eabi-7-2017-q4-major```

I have arm-none-eabi-gcc 16.2.0.

Either install the old gcc, or make changes to use the new gcc.
