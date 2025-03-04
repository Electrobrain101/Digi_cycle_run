#include <Adafruit_NeoPixel.h>

#define LED_PIN1   3    // Pin where the WS2811 data line is connected for the first LED strip
#define LED_PIN2   7    // Pin where the WS2811 data line is connected for the second LED strip
#define NUM_LEDS   100  // Number of LEDs in your strip

const byte interruptPin = 2;
const byte relayPins[4] = {8, 9, 10, 13};  // Pins for the SSR relays
// AAA
volatile unsigned long counter = 0;
unsigned long counter_current, counter_previous;
unsigned long lastTime, now;
bool moving = false;
bool secondStripLit = false;

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN2, NEO_GRB + NEO_KHZ800);

void sensor_check() {
  counter++;
}

void setup() {
  strip1.begin();
  strip1.show(); // Initialize all pixels to 'off'
  
  strip2.begin();
  strip2.show(); // Initialize all pixels to 'off'

  // Set all pixels on the first strip to white initially
  for (int i = 0; i < strip1.numPixels(); i++) {
    strip1.setPixelColor(i, strip1.Color(0, 160, 255)); // Set color of LED
  }
  strip1.show();

  // Set all pixels on the second strip to white initially
  for (int i = 0; i < strip2.numPixels(); i++) {
    strip2.setPixelColor(i, strip2.Color(0, 160, 255)); // Set color of LED
  }
  strip2.show();

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), sensor_check, CHANGE);

  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); // Ensure relays are off initially
  }

// digitalWrite(relayPins[3], HIGH); 
//   Serial.begin(9600);
//   lastTime = millis();
}

void loop() {
  now = millis();
  int timeChange = (now - lastTime);

  if (timeChange >= 1150) {
    if ((counter - counter_previous) > 10) {
      moving = true;
      Serial.println("moving");
    }

    if (abs(counter - counter_previous) < 2) {
      moving = false;
      Serial.println("not moving");
    }

    lastTime = now;
    counter_previous = counter;
  }

  static int litLeds1 = 0; // Number of LEDs currently lit in red on the first strip
  static int litLeds2 = 0; // Number of LEDs currently lit in the second strip

  if (moving) {
    // Cycle is moving, light up the first LEDs sequentially in red
    if (litLeds1 < strip1.numPixels()) {
      strip1.setPixelColor(litLeds1, strip1.Color(255, 160, 0)); // Set color to red
      litLeds1++;
      strip1.show();
      delay(200); // Delay to create the sequential effect

      // Turn on the relays sequentially after all LEDs in the first strip are lit
      if (litLeds1 == strip1.numPixels()) {
        for (int i = 0; i < 3; i++) {
          digitalWrite(relayPins[i], HIGH); // Turn on all three relay
          delay(2000); // Delay to create the sequential effect for relays
        }
      }
    }
    
    // After all relays are on, light up the second strip
    if (litLeds1 == strip1.numPixels() && litLeds2 < strip2.numPixels()) {
      strip2.setPixelColor(litLeds2, strip2.Color(255, 160, 0)); // Set color to green
      litLeds2++;
      strip2.show();
      delay(200); // Delay to create the sequential effect for the second strip

      if (litLeds2 == strip2.numPixels()) {
        digitalWrite(relayPins[3], HIGH); // Turn on the fourth relay
        secondStripLit = true; // Indicate that the second strip is completely lit
      }
    }
  } else {
    bool relaysAreOn = false;
    for (int i = 0; i < 3; i++) {
      if (digitalRead(relayPins[i]) == HIGH) {
        relaysAreOn = true;
        break;
      }
    }

    if (relaysAreOn) {
      // Turn off the fourth relay first
      if (secondStripLit) {
        digitalWrite(relayPins[3], LOW);
        secondStripLit = false;
        delay(2000); // Delay to create the sequential effect for the relay
      } else if (litLeds2 > 0) {


        
        // Turn off the second strip next
        litLeds2--;
        strip2.setPixelColor(litLeds2, strip2.Color(0, 160, 255)); // Turn off LED
        strip2.show();
        delay(100); // Delay to create the sequential effect for the second strip
      } else {
        // Turn off the remaining relays sequentially
        for (int i = 2; i >= 0; i--) {
          digitalWrite(relayPins[i], LOW); // Turn off relay
          delay(2000); // Delay to create the sequential effect for relays
        }
      }
    } else {
      // Relays are already off, decrease the LEDs on the first strip sequentially to white
      if (litLeds1 > 0) {
        litLeds1--;
        strip1.setPixelColor(litLeds1, strip1.Color(0, 160, 255)); // Set color to white
        strip1.show();
        delay(100); // Delay to create the sequential effect
      }
    }
  }
}
