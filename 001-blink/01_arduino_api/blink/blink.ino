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
*/
#define LED_PIN 13
#define DELAY_TIME_MS 1000

typedef enum {
  LED_OFF = LOW,
  LED_ON = HIGH //active high
} LED_STATE_T;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, LED_ON);
  delay(DELAY_TIME_MS);
  digitalWrite(LED_PIN, LED_OFF);
  delay(DELAY_TIME_MS);
}
