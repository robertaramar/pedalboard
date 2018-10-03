/**
 * Arduino/TeensyLC program to act as a pedal controller to a MIDI keyboard.
 *
 * Author: robert.schneider@aramar.de
 */

#include "PedalBoard.h"
#include "DrumtrackButton.hpp"
#include "KarmaSceneButton.hpp"
#include "MomentaryButton.hpp"
#include "PedalButton.hpp"
#include "ProgramChangeButton.hpp"

#define BOARD_NANO 1
#define BOARD_TEENSY 0

// For led chips like Neopixels, which have a data line, ground, and power, you
// just need to define DATA_PIN.  For led chipsets that are SPI based (four
// wires - data, clock, ground, and power), like the LPD8806 define both
// DATA_PIN and CLOCK_PIN
#define LED_DATA_PIN 16

/**
 * Button related constants. The board has 10 numbered buttons, an up and down,
 * a ctl and a mode button. Make a sum of 14 buttons.
 */

#define BUTTON_COUNT 2

/**
 * Button pins
 */
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

/**
 * Analog input pin for the volume pedal.
 */
#define VOLUME_PEDAL A3

/**
 * LED related constants. The board has 10 numbered buttons, an up and down, a
 * ctl and a mode button. Makes a sum of 13 buttons that have LEDs. The mode
 * button does not have an LED but a seven segment display.
 */
#define BRIGHTNESS 64
#define LED_COUNT 2
#define LED_BUTTON_01 0
#define LED_BUTTON_02 1
#define LED_BUTTON_03 2
#define LED_BUTTON_04 3
#define LED_BUTTON_05 4
#define LED_BUTTON_06 5
#define LED_BUTTON_07 6
#define LED_BUTTON_08 7
#define LED_BUTTON_09 8
#define LED_BUTTON_10 9
#define LED_BUTTON_CTL 10
#define LED_BUTTON_BANK_UP 11
#define LED_BUTTON_BANK_DOWN 12

//SoftwareSerial softSerial(4, 5);
// MIDI_CREATE_INSTANCE(SoftwareSerial, softSerial, midiS);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midiS);

// Define the array of leds
CRGB leds[LED_COUNT];

// PedalButton pedalButtons[BUTTON_COUNT];

PedalButton *pedalButtons[BUTTON_COUNT];

/**
 * Array holds all button objects that need processing during loop.
 */
// PedalButton pedalButtons[BUTTON_COUNT];

void setup() {
  Serial.begin(115000);
  while (!Serial && !Serial.available()) {
  }
  randomSeed(analogRead(0));
  // Pass log level, whether to show log level, and print interface.
  // Available levels are:
  // LOG_LEVEL_SILENT, LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, LOG_LEVEL_WARNING,
  // LOG_LEVEL_NOTICE, LOG_LEVEL_VERBOSE Note: if you want to fully remove all
  // logging code, uncomment #define DISABLE_LOGGING in Logging.h
  //       this will significantly reduce your project size

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);

  // Start logging
  Log.verbose("setup starts" CR);

  FastLED.addLeds<WS2811, LED_DATA_PIN, RGB>(leds, LED_COUNT);
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();

  midiS.setHandleNoteOn(handleNoteOn);
  midiS.setHandleClock(handleClock);
  midiS.setHandleProgramChange(handleProgramChange);
  midiS.setHandleControlChange(handleControlChange);

  midiS.begin(MIDI_CHANNEL_OMNI);

  /* pedalButtons[0] = new DrumtrackButton(BUTTON_01, LED_BUTTON_01);
  pedalButtons[0] = new KarmaSceneButton(KarmaSwitchMode::KarmaUp, 4, BUTTON_01,
                                         LED_BUTTON_01);
  pedalButtons[1] = new KarmaSceneButton(KarmaSwitchMode::KarmaDown, 4,
                                         BUTTON_02, LED_BUTTON_02); */
  pedalButtons[0] = new ProgramChangeButton(ProgramChangeMode::ProgramUp, 4,
                                            BUTTON_01, LED_BUTTON_01);
  pedalButtons[1] = new ProgramChangeButton(ProgramChangeMode::ProgramDown, 4,
                                            BUTTON_02, LED_BUTTON_02);
  for (int i = 0; i < BUTTON_COUNT; i++) {
    pedalButtons[i]->init();
  }
}

void loop() {
  midiS.read();
  for (int i = 0; i < BUTTON_COUNT; i++) {
    pedalButtons[i]->loop();
  }
}

void handleNoteOn(byte channel, byte note, byte velocity) {
  Log.verbose("Received note on %d on channel %d with velocity %d" CR, note,
              channel, velocity);
}

void handleClock() {
  for (int i = 0; i < BUTTON_COUNT; i++) {
    pedalButtons[i]->actOnClock();
  }
}

void handleProgramChange(byte channel, byte number) {
  for (int i = 0; i < BUTTON_COUNT; i++) {
    pedalButtons[i]->actOnProgramChange(channel, number);
  }
}

void handleControlChange(byte channel, byte number, byte value) {
  for (int i = 0; i < BUTTON_COUNT; i++) {
    pedalButtons[i]->actOnControlChange(channel, number, value);
  }
}

/**
 * Global method to change LED colors, used by the button methods.
 */
void switchLED(int ledIndex, CRGB colorCode) {
  if (leds[ledIndex] != colorCode) {
    leds[ledIndex] = colorCode;
    FastLED.show();
  }
}
