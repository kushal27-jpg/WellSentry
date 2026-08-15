# Hardware Wiring

The ESP32 is the main controller. It receives inputs from the vibration and ultrasonic sensors and controls the LEDs and buzzer.

| Component  | Pin  | ESP32    |
|------------|------|----------|
| SW-420     | DO   | GPIO 27  |
| SW-420     | VCC  | 3.3V     |
| SW-420     | GND  | GND      |
| HC-SR04    | TRIG | GPIO 5   |
| HC-SR04    | ECHO | GPIO 18  |
| HC-SR04    | VCC  | 5V       |
| HC-SR04    | GND  | GND      |
| Buzzer     | +    | GPIO 25  |
| Buzzer     | -    | GND      |
| Green LED  | +    | GPIO 26  |
| Yellow LED | +    | GPIO 14  |
| Red LED    | +    | GPIO 12  |

All components share a common ground.

> **Note:** The HC-SR04 ECHO signal must be voltage-divided before connecting to the ESP32 GPIO.
