# Project 003: USART
USART stands for Universal Synchronous and Asynchronous Serial Receiver and Transmitter.

## Documentation
ATmega328p Section 19, Page 143.

Page 144 - Diagram of USART components
Transimitter
- DATABUS to UDRn (Transmit)
- XCKn to Pin Control to Sync Logic to Mux leading to Transmit Shift Register
- TxDn, output of transmitter

USART supports 4 modes of clock operations:
- normal asynchronous
- double speed asynchronous
- master synchronous
- slave synchronous

^ I want to learn about the asynchronous mode(s) first
UMSELn ?and status register C (UCSRnC)? selects between asynchronous and synchronous (1 is sync, 0 probably asynchronous)

Page 145 - Clock Generation Logic, Block Diagram
- Shows UMSELn
- Shows U2Xn
- Shows Muxes
- Talks about Baud rate     //? baud meaning

Page 146
- Chart showing Baud Rate setting choice based on 4 modes of clock operation @ page 144

Page 147 - Frame Formats
- Frame is how data is formated
- Start bit
- Data: LSB to MSB
- Optional parity bit   //? parity bit meaning
- Stop bit

- Okay on communication line, start bit is low, end bit is high (aka IDLE)
- After frame completes: follow with new frame, or leave communication line IDLE

Page 148
- Tells what registers to use for frame format
    - UCSZn2:0 : Select num of data bits in frame
    - UPMn1:0  : Enable and set the type of parity bit
    - USBSn    : Selection between one or two stop bits
- Parity bit calculation
- USART Initialization
    - set baud rate
    - set frame format
    - enable transmitter or receiver depending on usage

Page 149 - USART Init code

Page 150 - USART Data Transmission code

Page 159 - Register Description

## How to View Bits Transmitted by ATmega328p
I am using a MacBook with iTerm2.
Recommendation is to use "screen" terminal command.

First check if device is available after plugging in Arduino Uno R3 board.
ls /dev/cu.*
One of the results should be /dev/cu.usbmodem1101

Then to see output use the 'screen' command.
screen /dev/cu.usbmodem1101 9600

