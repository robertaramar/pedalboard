
/**
 * Arduino/TeensyLC program to act as a pedal controller to a MIDI keyboard.
 *
 * Author: robert.schneider@aramar.de
 */

#include "LedController.hpp"
#include "PedalBoard.h"

#ifdef RGB_LED_SUPPORT
// Define the array of leds
CRGB LedController::rgbleds[RGB_LED_COUNT];
#endif

// create a global shift register object
// parameters: (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 LedController::shiftOut(2, 20, 19, 18);

/**
 * Delays for the LED init show
 */
#define LED_GAME_LONG_DELAY 2500
#define LED_GAME_SHORT_DELAY 500

/**
 * All required setup for controlling LEDs. If only standard LEDs are used, all
 * initializing is in the constructor of the shift-out register object.
 */
LedController::LedController() {
  Log.verbose("LedController constructor" CR);
#ifdef RGB_LED_SUPPORT
  FastLED.addLeds<WS2811, RGB_LED_DATA_PIN, RGB>(leds, RGB_LED_COUNT);
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  FastLED.setBrightness(RGB_LED_BRIGHTNESS);
  FastLED.show();
#endif
}

/**
 * Setup everything, make the init show run.
 */
void LedController::setup() {
  Log.verbose("LedController::setup entry" CR);
  // this->runInitShow();
  shiftOut.setAllHigh();
  Log.verbose("LedController::setup exit" CR);
}

/**
 * In case we introduce animation.
 */
void LedController::loop() {}

/**
 * Do a little fancy LED work when the board is started.
 */
void LedController::runInitShow() {
  Log.verbose("LedController::runInitShow setAllLow" CR);
  // setting all LEDs at the same time to LOW
  shiftOut.setAllLow();
  delay(LED_GAME_LONG_DELAY);

  Log.verbose("LedController::runInitShow setAllHigh" CR);
  // setting all LEDs at the same time to HIGH
  shiftOut.setAllHigh();
  delay(LED_GAME_LONG_DELAY);

  Log.verbose("LedController::runInitShow switching on one by one" CR);
  // setting single LEDs
  for (int i = 0; i < LED_COUNT; i++) {
    Log.verbose("switching on LED %d" CR, i);
    shiftOut.set(leds[i], LOW); // set single LED HIGH
    delay(LED_GAME_SHORT_DELAY);
  }

  Log.verbose("LedController::runInitShow switching off one by one" CR);
  // setting single LEDs
  for (int i = LED_COUNT - 1; i >= 0; i--) {
    Log.verbose("switching off LED %d" CR, i);
    shiftOut.set(leds[i], HIGH); // set single LED HIGH
    delay(LED_GAME_SHORT_DELAY);
  }

  Log.verbose("LedController::runInitShow switch on first row" CR);
  // set all pins at once
  uint8_t pinValues[] = {B0000000, B1111111};
  shiftOut.setAll(pinValues);
  delay(LED_GAME_LONG_DELAY);

  Log.verbose("LedController::runInitShow switch on second row" CR);
  // set all pins at once
  pinValues[0] = B1111111;
  pinValues[1] = B0000000;
  shiftOut.setAll(pinValues);
  delay(LED_GAME_LONG_DELAY);

  shiftOut.setAllHigh();
  Log.verbose("LedController::runInitShow exit" CR);
}

/**
 * Global method to change LED colors, used by the button methods.
 */
void LedController::switchLed(int ledIndex, CRGB colorCode) {
#ifdef RGB_LED_SUPPORT
  this->switchRgbLed(ledIndex, colorCode);
#else
  this->switchLed(ledIndex, !(colorCode.r + colorCode.g + colorCode.b == 0));
#endif
}

/**
 * Global method to change LED colors, used by the button methods.
 */
void LedController::switchLed(int ledIndex, boolean on) {
  // switch LED on/off
  // NOTE: The Roland boards switches ground to make the LEDs shine
  shiftOut.set(ledIndex, on ? LOW : HIGH);
}

#ifdef RGB_LED_SUPPORT
/**
 * Global method to change LED colors, used by the button methods.
 */
void LedController::switchRgbLed(int ledIndex, CRGB colorCode) {
  if (rgbleds[ledIndex] != colorCode) {
    rgbleds[ledIndex] = colorCode;
    FastLED.show();
  }
}
#endif
