/**
 * Arduino/TeensyLC program to act as a pedal controller to a MIDI keyboard.
 * 
 * Author: robert.schneider@aramar.de
 */

#include <Bounce2.h>
#include <MIDI.h>
#include <FastLED.h>
#include "PedalButton.h"

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define LED_DATA_PIN 3

/**
 * LED related constants. The board has 10 numbered buttons, an up and down and a ctrl button.
 * Makes a sum of 13 buttons which all have LEDs.
 */
#define LED_COUNT 1
#define LED_BUTTON_01 0

MIDI_CREATE_DEFAULT_INSTANCE();

// Define the array of leds
CRGB leds[LED_COUNT];

void setup() { 
      FastLED.addLeds<WS2811, LED_DATA_PIN, RGB>(leds, LED_COUNT);
      MIDI.begin();
}

void loop() { 
  // Turn the LED on, then pause
  leds[0] = CRGB::Yellow;
  FastLED.show();
  delay(500);
  // Turn the LED on, then pause
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(500);
  // Turn the LED on, then pause
  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(500);
  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
}
