# Project 003: USART
USART stands for Universal Synchronous and Asynchronous Serial Receiver and Transmitter.

## Documentation
ATmega328p Section 19, Page 143.

Page 152 - Data Reception - The USART Receiver

## How to View Bits Transmitted by ATmega328p
I am using a MacBook with iTerm2.
Recommendation is to use "screen" terminal command.

First check if device is available after plugging in Arduino Uno R3 board.
ls /dev/cu.*
One of the results should be /dev/cu.usbmodem1101

Then to see output use the 'screen' command.
screen /dev/cu.usbmodem1101 9600

To exit screen:
CTRL-A KY
