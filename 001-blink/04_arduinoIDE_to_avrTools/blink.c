/*
Author: Ammar Mohammed
Date: 2026-06-[26,27]
Program: Blink w/ Memory Mapped Registers & No Setup/Loop

Board: Arduino AVR Boards > Arduino Uno
Physical Board: Arduino Uno R3
Port: /dev/cu.usbmodem1101

AVR Tools (that came installed with Arduino IDE) were used to compile and upload this sketch.

Resources:
- https://docs.arduino.cc/language-reference/
* Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet
* Arduino Uno R3 Circuit Schematic
*/

#include <stdint.h>

#define MyPORTB *((volatile uint8_t*)(0x25))
#define MyDDRB *((volatile uint8_t*)(0x24))

int main(void) {
  MyDDRB |= (1 << 5);

  while(1) {
    MyPORTB |= (1 << 5);
    for(volatile long i = 0; i < 500000; i++) {}
    MyPORTB &= ~(1 << 5);
    for(volatile long i = 0; i < 500000; i++) {}
  }

  return 0;
}
