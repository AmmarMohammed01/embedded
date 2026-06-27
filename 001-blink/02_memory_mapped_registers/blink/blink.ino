/*
Author: Ammar Mohammed
Date: 2026-06-26
Program: Blink using Arduino APIs

Board: Arduino AVR Boards > Arduino Uno
Physical Board: Arduino Uno R3
Port: /dev/cu.usbmodem1101

Arduino IDE used to compile and upload this sketch.

Resources:
- https://docs.arduino.cc/language-reference/
* Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet
  - P.3 Pin Descriptions
  - P.19 I/O Memory
    - pages 10 and 19 discuss I/O memory space.
    - page 19 states: "When addressing I/O registers as data space using LD and ST instructions, 0x20 must be added to these addresses."
  - P.20 AVR Memories Register Description
  * P.58 I/O Ports
    - Pxn can be replaced with PB5. B is numbering letter for port. 5 is bit number.
    - Datasheet p.58 even points to p.72 for physical i/o registers and bit locations
    - "Three I/O memory address locations are allocated for each port..."
    This describes PORTx, DDRx, and PINx.
    - PORTx Data Register
    - DDRx Data Direction Register (Read & Write)
    - PINx Port Input Pins (Read Only)
  * P.72 I/O Ports Register Description: PORTB, DDRB, PINB
    - Discard PINB since it is for Pin Input
    - I need Pin Output to interface LED, use PORTB and DDRB
    - DDRB Set 5th bit to Output
    - PORTB Need to toggle 5th bit to turn LED_ON and LED_OFF
  - P.241 Memory Programming
  - P.275 Register Summary
* Arduino Uno R3 Circuit Schematic
  - I know there are 4 LEDs on Arduino Uno R3 board
  - ON GREEN LED is in top right corner of schematic
  - TX & RX YELLOW LEDs are at bottom center of schematic
  * L YELLOW LED is at top center of schematic
    - I am trying to find out how the LED is connected to Pin 13
    - The OP-AMP pin 5 is connected to SCK,
    which is also found on ATMEGA328P-PU as (SCK)PB5.
    That same pin leads to the headers, which has the # 13 labeled in green
    - Now I see it is labeled (SCK)PB5, I should refer to Atmel Datasheet
*/
#define IO_REGISTER_OFFSET 0x20
#define PORTB_ADDRESS 0x05
#define DDRB_ADDRESS 0x04

/*
volatile byte* cast is saying: this value is an address; since it is volatile compiler shouldn't remove it.

Then I am dereferencing the address to interface with the value at that memory location.
*/
#define MyPORTB *( (volatile byte*)(PORTB_ADDRESS + IO_REGISTER_OFFSET) )
#define MyDDRB *( (volatile byte*)(DDRB_ADDRESS + IO_REGISTER_OFFSET) )

void setup() {
  // (1 << 5) Set the 5th bit to a value of 1
  // |= Leave other bits the same, if bit 5 is 0 set it to 1
  MyDDRB |= (1 << 5);
}

void loop() {
  MyPORTB |= (1 << 5);
  for(long i = 0; i < 1000000; i++) {MyPORTB |= (1 << 5);} //delay(DELAY_TIME_MS);
  MyPORTB &= ~(1 << 5);
  for(long i = 0; i < 1000000; i++) {MyPORTB &= ~(1 << 5);} //delay(DELAY_TIME_MS);
}
