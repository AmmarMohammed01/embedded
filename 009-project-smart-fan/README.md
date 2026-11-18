## Embedded Concepts To Use
- ADC: Temperature Sensor
- PWM & Timer: Motor
- I2C: OLED Screen and/or Temperature Sensor
- UART: Debugging (for now)
- GPIO: Buttons & LEDs
- EEPROM: device mode setting

- Interrupts: Possibly temperature sensor

## Description
The "smart fan" project is a mock project that I will use to demonstrate embedded peripherals I have learned about.

The smart fan can run in one of two modes:
- Manual mode:
    - user can turn the fan on/off using buttons.
    - user can adjust fan speed with potentiometer.
- Smart mode:
    - the fan will activate based on the temperature.
    - (possible feature addition) the fan will rise to higher speeds as the temperature ascends.

The user will know which mode the fan is in as indicated through the LEDs.

The user can select the mode by using the button.

The mode setting will be saved in EEPROM, so the next time the same mode will be used on startup.

The OLED display will show the temperature.
- (possible feature addition) user can switch what temperature units are shown on display.

Future Improvement:
- Combine this project with the ESP32 to host a webserver displaying the temperature reading.
