
/**
 * Arduino/TeensyLC program to act as a pedal controller to a MIDI keyboard.
 *
 * Author: robert.schneider@aramar.de
 */
#pragma once

#define FASTLED_INTERNAL
#include <FastLED.h>
#include <ShiftRegister74HC595.h>

// For led chips like Neopixels, which have a data line, ground, and power, you
// just need to define DATA_PIN.  For led chipsets that are SPI based (four
// wires - data, clock, ground, and power), like the LPD8806 define both
// DATA_PIN and CLOCK_PIN
#ifdef RGB_LED_SUPPORT
#define RGB_LED_DATA_PIN 16
#define RGB_LED_COUNT 2
#define RGB_LED_BRIGHTNESS 64
#endif

#define LED_COUNT 13 // there are 13 LEDs P1-P10, Bank down, Bank up, CTL

/**
 * LED related constants. The board has 10 numbered buttons, an up and down, a
 * ctl and a mode button. Makes a sum of 13 buttons that have LEDs. The mode
 * button does not have an LED but a seven segment display.
 */
#define LED_BUTTON_01 1        // Bit 0 in lower byte
#define LED_BUTTON_02 7        // Bit 1 in lower byte
#define LED_BUTTON_03 6        // Bit 2 in lower byte
#define LED_BUTTON_04 5        // Bit 3 in lower byte
#define LED_BUTTON_05 4        // Bit 4 in lower byte
#define LED_BUTTON_BANK_DOWN 3 // Bit 5 in lower byte
#define LED_BUTTON_CTL 2       // Bit 6 in lower byte
#define LED_UNUSED_1 8         // Bit 7 in lower byte

#define LED_UNUSED_2 9        // Bit 0 in upper byte
#define LED_BUTTON_06 10      // Bit 1 in upper byte
#define LED_BUTTON_07 11      // Bit 2 in upper byte
#define LED_BUTTON_08 12      // Bit 3 in upper byte
#define LED_BUTTON_09 13      // Bit 4 in upper byte
#define LED_BUTTON_10 14      // Bit 5 in upper byte
#define LED_BUTTON_BANK_UP 15 // Bit 6 in upper byte
#define LED_UNUSED_3 16       // Bit 7 in upper byte

class LedController {
private:
  /** The shift-out register interface */
  static ShiftRegister74HC595 shiftOut;
  /** All used LEDs in an array   */
  uint8_t leds[LED_COUNT] = {
      LED_BUTTON_01,        LED_BUTTON_02,  LED_BUTTON_03,     LED_BUTTON_04, LED_BUTTON_05,
      LED_BUTTON_BANK_DOWN, LED_BUTTON_CTL, LED_BUTTON_06,     LED_BUTTON_07, LED_BUTTON_08,
      LED_BUTTON_09,        LED_BUTTON_10,  LED_BUTTON_BANK_UP};

public:
  /**
   * Constructor to initialize stuff. Does init of CRGB controller if enabled.
   */
  LedController();
  /**
   * Required to be called if initialization is required (as of yet is NOT).
   * However, the method calls the runInitGame to make the LEDs to some fancy
   * lighting.
   */
  void setup();
  /**
   * Call this if animation is required (as of yet is NOT).
   */
  void loop();
  /**
   * Utility method to change the color of an LED (use CRGB::Black to switch
   * off)
   */
  void switchLed(int ledIndex, CRGB colorCode);

private:
  void runInitShow();
  void switchLed(int ledIndex, boolean on);
#ifdef RGB_LED_SUPPORT
  void switchRgbLed(int ledIndex, CRGB colorCode);
#endif
};