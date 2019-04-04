/**
 * Arduino/Teensy program to act as a pedal controller to a MIDI keyboard.
 *
 * Author: robert.schneider@aramar.de
 */

#include "AnalogControl.hpp"
#include "DrumtrackButton.hpp"
#include "KarmaSceneButton.hpp"
#include "LedController.hpp"
#include "MomentaryButton.hpp"
#include "PedalBoard.h"
#include "PedalButton.hpp"
#include "ProgramChangeButton.hpp"

/**
 * Button assignments
 */

#define BUTTON_01 6
#define BUTTON_02 0
#define BUTTON_03 1
#define BUTTON_04 2
#define BUTTON_05 3
#define BUTTON_BANK_DOWN 4
#define BUTTON_CTL 5

#define BUTTON_06 8
#define BUTTON_07 9
#define BUTTON_08 10
#define BUTTON_09 11
#define BUTTON_10 12
#define BUTTON_BANK_UP 13

#define BUTTON_MODE 14

/**
 * Analog input pin for the volume pedal.
 */
#define VOLUME_PEDAL A2

// PedalButton pedalButtons[BUTTON_COUNT];

PedalButton *pedalButtons[16];
AnalogControl *analogControl;

LedController *ledController = new LedController();

uint16_t numberOfButtons = 0;

/**
 * Array holds all button objects that need processing during loop.
 */
// PedalButton pedalButtons[BUTTON_COUNT];

void setup() {

  randomSeed(analogRead(0));

  // Pass log level, whether to show log level, and print interface.
  // Available levels are:
  // LOG_LEVEL_SILENT, LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, LOG_LEVEL_WARNING,
  // LOG_LEVEL_NOTICE, LOG_LEVEL_VERBOSE Note: if you want to fully remove all
  // logging code, uncomment #define DISABLE_LOGGING in Logging.h
  //       this will significantly reduce your project size
#if LOGGING
  Serial.begin(115000);
  Log.begin(LOG_LEVEL_TRACE, &Serial);
#else
  Log.begin(LOG_LEVEL_SILENT, &Serial);
#endif

  // Start logging
  Log.verbose("setup starts" CR);

  usbMIDI.setHandleNoteOn(handleNoteOn);
  usbMIDI.setHandleClock(handleClock);
  usbMIDI.setHandleProgramChange(handleProgramChange);
  usbMIDI.setHandleControlChange(handleControlChange);

  usbMIDI.begin();

  // Start button assignment
  pedalButtons[numberOfButtons++] = new DrumtrackButton(BUTTON_01, LED_BUTTON_01);
  pedalButtons[numberOfButtons++] =
      new KarmaSceneButton(KarmaSwitchMode::KarmaUp, 4, BUTTON_02, LED_BUTTON_02);
  pedalButtons[numberOfButtons++] =
      new KarmaSceneButton(KarmaSwitchMode::KarmaDown, 4, BUTTON_06, LED_BUTTON_06);
  pedalButtons[numberOfButtons++] =
      new ProgramChangeButton(ProgramChangeMode::ProgramUp, 4, BUTTON_03, LED_BUTTON_03);
  pedalButtons[numberOfButtons++] =
      new ProgramChangeButton(ProgramChangeMode::ProgramDown, 4, BUTTON_07, LED_BUTTON_07);

  /**
   * Initialize all pedal buttons and call their init methods.
   *
  pedalButtons[numberOfButtons++] = new MomentaryButton(BUTTON_01, LED_BUTTON_01);
  pedalButtons[numberOfButtons++] = new MomentaryButton(BUTTON_02, LED_BUTTON_02);
  pedalButtons[numberOfButtons++] = new MomentaryButton(BUTTON_03, LED_BUTTON_03);
  pedalButtons[numberOfButtons++] = new MomentaryButton(BUTTON_04, LED_BUTTON_04);
  pedalButtons[numberOfButtons++] = new MomentaryButton(BUTTON_05, LED_BUTTON_05);
  pedalButtons[numberOfButtons++] = new MomentaryButton(BUTTON_BANK_DOWN, LED_BUTTON_BANK_DOWN);
  pedalButtons[numberOfButtons++] = new MomentaryButton(BUTTON_CTL, LED_BUTTON_CTL);
  pedalButtons[numberOfButtons++] = new MomentaryButton(BUTTON_06, LED_BUTTON_06);
  pedalButtons[numberOfButtons++] = new MomentaryButton(BUTTON_07, LED_BUTTON_07);
  pedalButtons[numberOfButtons++] = new MomentaryButton(BUTTON_08, LED_BUTTON_08);
  pedalButtons[numberOfButtons++] = new MomentaryButton(BUTTON_09, LED_BUTTON_09);
  pedalButtons[numberOfButtons++] = new MomentaryButton(BUTTON_10, LED_BUTTON_10);
  pedalButtons[numberOfButtons++] = new MomentaryButton(BUTTON_BANK_UP, LED_BUTTON_BANK_UP);
  */

  for (int i = 0; i < numberOfButtons; i++) {
    pedalButtons[i]->init();
  }

  /**
   * Initialize the analog control for the pedal and call its init methods.
   */
  analogControl = new AnalogControl();
  analogControl->init();

  // Initialize the shift-in register to obtain button states
  BounceShiftIn::setup(15, 14, 13);

  ledController->setup();

  Log.verbose("setup done" CR);
}

static long themillis = 0;

void loop() {
  usbMIDI.read();

  uint16_t currentState = BounceShiftIn::loop();

  if (millis() - themillis > 1000) {
    Log.verbose("currentState = %B" CR, currentState, 0);
    themillis = millis();
  }

  for (int i = 0; i < numberOfButtons; i++) {
    pedalButtons[i]->loop();
  }
  analogControl->loop();

  usbMIDI.read();
}

void handleNoteOn(byte channel, byte note, byte velocity) {
  Log.verbose("Received note on %d on channel %d with velocity %d" CR, note, channel, velocity);
}

void handleClock() {
  for (int i = 0; i < numberOfButtons; i++) {
    pedalButtons[i]->actOnClock();
  }
}

void handleProgramChange(byte channel, byte number) {
  for (int i = 0; i < numberOfButtons; i++) {
    pedalButtons[i]->actOnProgramChange(channel, number);
  }
}

void handleControlChange(byte channel, byte number, byte value) {
  for (int i = 0; i < numberOfButtons; i++) {
    pedalButtons[i]->actOnControlChange(channel, number, value);
  }
}

/**
 * Proxy methode to redirect call into the LedController object.
 */
void switchLed(int ledIndex, CRGB colorCode) { ledController->switchLed(ledIndex, colorCode); }
