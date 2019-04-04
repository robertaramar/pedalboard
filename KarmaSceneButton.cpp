/**
 * Implementation of a KarmaSceneButton that knows how to switch on/off the
 * drumtrack on the KRONOS.
 *
 * Author: robert.schneider@aramar.de
 */
#include "KarmaSceneButton.hpp"
#include "PedalBoard.h"

// Not used any longer, using CC85 now
// SysEx to switch to a different Karma scene. Last byte holds the Karma scene
// number (0 - 7).
// byte KarmaSceneButton::m_karmaSwitchSysEx[] = {
//    0x42, 0x30, 0x68, 0x6d, 0x02, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x00, 0x00};

CRGB::HTMLColorCode KarmaSceneButton::m_colorCodes[] = {
    CRGB::Red,    CRGB::Green,  CRGB::Blue,      CRGB::Yellow,
    CRGB::Violet, CRGB::Salmon, CRGB::Chocolate, CRGB::Orange};

int8_t KarmaSceneButton::m_currentScene = 0;

KarmaSceneButton::KarmaSceneButton(KarmaSwitchMode mode, int8_t fixedScene, int8_t buttonPin,
                                   int8_t ledIndex)
    : PedalButton(buttonPin, ledIndex) {
  m_switchMode = mode;
  m_fixedScene = fixedScene;
  Log.trace("KarmaSceneButton constructor" CR);
}

void KarmaSceneButton::actOnDown() {
  Log.trace("%l KarmaSceneButton actOnDown" CR, millis());
  switchLed(m_ledIndex, CRGB::Red);
  switchKarmaScene();
}

void KarmaSceneButton::actOnLongDown() {
  Log.trace("%l KarmaSceneButton actOnLongDown" CR, millis());
  m_currentScene = -1;
  switchKarmaScene();
}

void KarmaSceneButton::actOnUp() {
  switchLed(m_ledIndex, CRGB::Black);
  Log.trace("%l KarmaSceneButton actOnUp" CR, millis());
}

void KarmaSceneButton::actOnLongUp() {
  switchLed(m_ledIndex, CRGB::Black);
  Log.trace("%l KarmaSceneButton actOnLongUp" CR, millis());
}

void KarmaSceneButton::actOnClock() {
  // switchLed(m_ledIndex, m_colorCodes[m_currentScene]);
}

void KarmaSceneButton::actOnProgramChange(byte channel, byte number) {
  if (channel == KRONOS_CHANNEL) {
    Log.trace("%l KarmaSceneButton actOnProgramChange, m_currentScene = 0" CR, millis());
    m_currentScene = 0;
  }
}

void KarmaSceneButton::actOnControlChange(byte channel, byte number, byte value) {
  if (channel == KRONOS_CHANNEL && number == 85) {
    m_currentScene = value;
  }
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

  Log.trace("%l KarmaSceneButton switch to scene %d" CR, millis(), m_currentScene);

  usbMIDI.sendControlChange(85, m_currentScene, KRONOS_CHANNEL);
  // m_karmaSwitchSysEx[sizeof(m_karmaSwitchSysEx) - 1] = m_currentScene;
  // usbMIDI.sendSysEx(sizeof(m_karmaSwitchSysEx), m_karmaSwitchSysEx);
}
