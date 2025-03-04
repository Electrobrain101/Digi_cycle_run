# Digi_cycle_run
## Project Description

This project controls two WS2811 LED strips and a series of relays using an Arduino board. It is designed to create a dynamic visual and control system for automation, such as in a display, lighting system, or any other application requiring sequential lighting and relay activation. The system uses an hall sensor used in the gym cycle or any other interrupt-based input to determine movement and trigger various lighting effects and relay activations in sequence.

### Features:
- **LED Strip Control:** Controls two WS2811 RGB LED strips connected to two separate pins on the Arduino. LEDs light up in sequence with different colors based on movement detection.
- **Relay Control:** Controls up to four Solid-State Relays (SSRs) connected to the Arduino, triggering sequentially based on the movement of an object detected by a sensor.
- **Movement Detection:** Uses an interrupt pin (pin 2) to detect changes in state (e.g., movement detection) and toggles the lighting and relay system accordingly.
- **Sequential Effects:** Both LED strips and relays are activated sequentially with configurable delays between actions, allowing for dynamic visual and control effects.
- **Adjustable LED Effects:** The first LED strip starts lighting up in a red color, while the second strip follows with a green color, with a time delay between each LED turning on.
- **Efficient Power Management:** Relays are activated in a controlled manner, ensuring that devices connected to the relays are powered on/off in sequence, providing energy-efficient operation.

### Hardware Required:
- 2 WS2811 RGB LED strips
- 4 SSR (Solid-State Relays)
- Arduino board (e.g., Arduino Uno)
- Infrared sensor or any suitable interrupt-based motion detection sensor
- Power supply for LEDs and relays
- Jumper wires for connections

### Pinout Configuration:
- **LED_PIN1 (Pin 3):** Controls the first WS2811 LED strip.
- **LED_PIN2 (Pin 7):** Controls the second WS2811 LED strip.
- **Interrupt Pin (Pin 2):** Used for motion detection or other interrupt-based input.
- **Relay Pins (Pins 8, 9, 10, 13):** Controls the state of four relays.

### Key Variables:
- **`counter`**: A counter variable that increments each time the sensor detects a change in state (e.g., motion).
- **`moving`**: A flag to determine if the object is moving based on the sensor input.
- **`litLeds1`, `litLeds2`**: Track the number of LEDs lit on each strip, ensuring the LEDs light up in sequence.
- **`secondStripLit`**: A flag indicating if the second LED strip has been fully lit.
  
### Logic:
1. **Movement Detection:** The system detects changes using the interrupt pin and evaluates whether movement is detected.
2. **LED Control:** When movement is detected, the first LED strip lights up in sequence, followed by the second strip. Once both strips are fully lit, the relays are activated sequentially.
3. **Relay Control:** After lighting the LEDs, the relays are switched on one after another. Once the movement stops, the system gradually turns off the LEDs and relays in reverse order.
4. **Sequential Effects:** The lighting and relay activation/deactivation occurs in a controlled, sequential manner with customizable time delays to create visually appealing effects.

### Libraries:
- **Adafruit NeoPixel:** Used for controlling the WS2811 RGB LED strips. 

### How to Use:
1. Upload the code to your Arduino board.
2. Ensure the WS2811 LED strips are properly connected to the defined pins.
3. Ensure the relays and sensors are connected and configured.
4. When motion is detected, the LEDs will light up sequentially, followed by the activation of relays. When motion stops, the LEDs and relays will deactivate in reverse order.

This project demonstrates the interaction of LEDs and relays based on real-time sensor inputs, and it can be further expanded for more complex automation tasks or used as the base for a more intricate lighting control system.
