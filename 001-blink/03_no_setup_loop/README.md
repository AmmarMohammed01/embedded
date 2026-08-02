# Project: Blink an LED (Avoid setup(), loop(), and byte)
## About
### Materials
- **Microcontroller**: Arduino Uno R3.
- **Laptop** w/ **Arduino IDE** software.
- **USB Cable** to upload code from Arduino IDE to Arduino Uno R3 board.

### Summary
- On Arduino Uno R3 board, blink the on-board LED
- Avoid more of the Arduino framework (described below)

### Details
- **ATmega328p Datasheet** used to find out **addresses** of **GPIO pins**.
- **Macros** used to define **register addresses** and **derefernce** them to access values.
- Used **bit manipulation** to **set** ```OUTPUT``` data direction and **toggle** output value to ```LOW``` and ```HIGH```
- ```volatile``` keyword used to make sure value at register address is manipulated and checked every time instruction calls the register.
- Made use of Arduino .ino sketches.
- Used setup() and loop() functions.
- Use Arduino IDE to program the microcontroller.
- **Avoided** Arduino Framework functions such as pinMode(), digitalWrite(), and delay(). Also avoided setup(), loop(), and byte.
    - Now using int main(). Begin of main initializes the output pin, replacing Arduino setup(). The while loop toggles the pin output, replacing Arduino loop().
    - Included stdint.h. Library brings datatype ```uint8_t``` which is an unsigned 8-bit integer, this replaces Arduino from importing it's ```byte``` type definition.
    - DDRB (Data Direction Register B): Replaces purpose of pinMode(); allows IO13 pin of Arduino to be set as OUTPUT.
    - PORTB: Replaces purpose of digitalWrite(); allows IO13 of Arduino to be set as LOW or HIGH
    - for loop: used to semi-replace the delay() function. Instead of using a software delay, a for loop is used to run many instructions, acting as a delay of sorts.

## How to run
1. Open Arduino IDE
2. Open folder ```blink``` containing to ```blink.ino``` Arduino sketch
3. Select board as ```Arduino Uno R3``` and select correct USB port
4. Press the ```Upload``` button
