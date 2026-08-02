# Project: Blink an LED (Basic Arduino Framework Implementation)
## About
### Materials
- **Microcontroller**: Arduino Uno R3.
- **Laptop** w/ **Arduino IDE** software.
- **USB Cable** to upload code from Arduino IDE to Arduino Uno R3 board.

### Summary
- On Arduino Uno R3 board, blink the on-board LED
- Blink the LED every second

### Details
- Use Arduino IDE to program the microcontroller.
- Made use of Arduino .ino sketches.
- Used setup() and loop() functions.
- Used pinMode() and digitalWrite() to interface the on-board LED.
- Used delay() to block code execution for specified time of 1000ms
- Used macros to define pin number and delay time
- Used enum to clarify LED is connected as an Active High component rather than Active Low

## How to run
1. Open Arduino IDE
2. Open folder ```blink``` containing to ```blink.ino``` Arduino sketch
3. Select board as ```Arduino Uno R3``` and select correct USB port
4. Press the ```Upload``` button
