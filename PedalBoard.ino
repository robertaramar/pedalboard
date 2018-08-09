/**
 * Arduino/TeensyLC program to act as a pedal controller to a MIDI keyboard.
 * 
 * Author: robert.schneider@aramar.de
 */

#include <MIDI.h>
#include <FastLED.h>
#include "PedalButton.hpp"

#define BOARD_NANO 1
#define BOARD_TEENSY 0

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define LED_DATA_PIN 16

/**
 * Button related constants. The board has 10 numbered buttons, an up and down, a ctl and a mode button.
 * Make a sum of 14 buttons.
 */

#define BUTTON_COUNT 14
#define BUTTON_MODE 2
#define BUTTON_CTL 3
#define BUTTON_BANK_UP 4
#define BUTTON_BANK_DOWN 5
#define BUTTON_01 6
#define BUTTON_02 7
#define BUTTON_03 8
#define BUTTON_04 9
#define BUTTON_05 10
#define BUTTON_06 11
#define BUTTON_07 12
#define BUTTON_08 13
#define BUTTON_09 14
#define BUTTON_10 15

#define VOLUME_PEDAL A3

/**
 * LED related constants. The board has 10 numbered buttons, an up and down, a ctl and a mode button.
 * Makes a sum of 13 buttons that have LEDs. The mode button does not have an LED but a seven segment display.
 */
#define LED_COUNT 1
#define LED_BUTTON_CTL 0
#define LED_BUTTON_BANK_UP 1
#define LED_BUTTON_BANK_DOWN 2
#define LED_BUTTON_01 3
#define LED_BUTTON_02 4
#define LED_BUTTON_03 5
#define LED_BUTTON_04 6
#define LED_BUTTON_05 7
#define LED_BUTTON_06 8
#define LED_BUTTON_07 9
#define LED_BUTTON_08 10
#define LED_BUTTON_09 11
#define LED_BUTTON_10 12

MIDI_CREATE_DEFAULT_INSTANCE();

// Define the array of leds
CRGB leds[LED_COUNT];

/**
 * Array holds all button objects that need processing during loop.
 */
// PedalButton pedalButtons[BUTTON_COUNT];

void setup()
{
  FastLED.addLeds<WS2811, LED_DATA_PIN, RGB>(leds, LED_COUNT);
  MIDI.begin();
  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    // pedalButtons[i].init();
  }
}

void loop()
{
  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    // pedalButtons[i].loop();
  }
}
