/**
 * Implementation of a KarmaSceneButton that knows how to switch on/off the
 * drumtrack on the KRONOS.
 *
 * Author: robert.schneider@aramar.de
 */
#include <ArduinoLog.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <MIDI.h>
#include <SoftwareSerial.h>
#include "KarmaSceneButton.hpp"
#include "PedalBoard.h"

// SysEx to switch to a different Karma scene. Last byte holds the Karma scene
// number (0 - 7).
byte KarmaSceneButton::m_karmaSwitchSysEx[] = {
    0x42, 0x30, 0x68, 0x6d, 0x02, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x00, 0x00};

CRGB::HTMLColorCode KarmaSceneButton::m_colorCodes[] = {
    CRGB::Red,    CRGB::Green,  CRGB::Blue,      CRGB::Yellow,
    CRGB::Violet, CRGB::Salmon, CRGB::Chocolate, CRGB::Orange};

KarmaSceneButton::KarmaSceneButton(KarmaSwitchMode mode, int8_t fixedScene,
                                   int8_t buttonPin, int8_t ledIndex)
    : PedalButton(buttonPin, ledIndex) {
  m_switchMode = mode;
  m_fixedScene = fixedScene;
  Log.verbose("KarmaSceneButton constructor" CR);
}

void KarmaSceneButton::actOnDown() {
  Log.verbose("%l KarmaSceneButton actOnDown" CR, millis());
  switchKarmaScene();
}

void KarmaSceneButton::actOnLongDown() {
  Log.verbose("%l KarmaSceneButton actOnLongDown" CR, millis());
  m_currentScene = -1;
  switchKarmaScene();
}

void KarmaSceneButton::actOnUp() {
  Log.verbose("%l KarmaSceneButton actOnUp" CR, millis());
}

void KarmaSceneButton::actOnLongUp() {
  Log.verbose("%l KarmaSceneButton actOnLongUp" CR, millis());
}

void KarmaSceneButton::actOnClock() {
}

void KarmaSceneButton::switchKarmaScene() {
  switch (m_switchMode) {
    case KarmaUp:
      m_currentScene++;
      break;
    case KarmaDown:
      m_currentScene--;
      break;
    case KarmaScene:
      m_currentScene = m_fixedScene;
      break;
  }

  if (m_currentScene < 0) {
    m_currentScene = 7;
  }

  if (m_currentScene > 7) {
    m_currentScene = 0;
  }

  Log.verbose("%l KarmaSceneButton swtich to scene %d" CR, millis(),
              m_currentScene);

  m_karmaSwitchSysEx[sizeof(m_karmaSwitchSysEx) - 1] = m_currentScene;
  midiS.sendSysEx(sizeof(m_karmaSwitchSysEx), m_karmaSwitchSysEx);

  switchLED(m_ledIndex, m_colorCodes[m_currentScene]);
}
