/**
 * Implementation of a DrumtrackButton that knows how to switch on/off the
 * drumtrack on the KRONOS.
 *
 * Author: robert.schneider@aramar.de
 */
#include "DrumtrackButton.hpp"
#include "PedalBoard.h"

byte DrumtrackButton::m_drumTrackSysEx[] = {0x42, 0x30, 0x68, 0x6e, 0x01, 0x00,
                                            0x00, 0x0a, 0x00, 0x00, 0x00, 0x01};

DrumtrackButton::DrumtrackButton(int8_t buttonPin, int8_t ledIndex)
    : PedalButton(buttonPin, ledIndex) {
  Log.verbose("DrumtrackButton constructor" CR);
}

void DrumtrackButton::actOnDown() {
  Log.verbose("%l DrumtrackButton actOnDown" CR, millis());
  switchDrumTrack(!m_isRunning);
}

void DrumtrackButton::actOnLongDown() {
  Log.verbose("%l DrumtrackButton actOnLongDown" CR, millis());
  switchLED(m_ledIndex, CRGB::Blue);
  m_currentColorCode = CRGB::Blue;
}

void DrumtrackButton::actOnUp() {
  Log.verbose("%l DrumtrackButton actOnUp" CR, millis());
}

void DrumtrackButton::actOnLongUp() {
  Log.verbose("%l DrumtrackButton actOnLongUp" CR, millis());
  switchDrumTrack(false);
}

void DrumtrackButton::actOnClock() {
  if (m_isRunning) {
    if (m_currentClock++ == 0) {
      switchLED(m_ledIndex, m_currentColorCode);
    }
    if (m_currentClock == 6) {
      switchLED(m_ledIndex, CRGB::Black);
    }
    if (m_currentClock >= 24) {
      m_currentClock = 0;
    }
  }
}

void DrumtrackButton::actOnProgramChange(byte channel, byte number) {}

void DrumtrackButton::actOnControlChange(byte channel, byte number,
                                         byte value) {}

void DrumtrackButton::switchDrumTrack(boolean on) {
  if (on) {
    m_drumTrackSysEx[sizeof(m_drumTrackSysEx) - 1] = 0x01;
    midiS.sendSysEx(sizeof(m_drumTrackSysEx), m_drumTrackSysEx);
    switchLED(m_ledIndex, CRGB::Green);
    m_currentColorCode = CRGB::Green;
    m_currentClock = 0;
  } else {
    m_drumTrackSysEx[sizeof(m_drumTrackSysEx) - 1] = 0x00;
    midiS.sendSysEx(sizeof(m_drumTrackSysEx), m_drumTrackSysEx);
    switchLED(m_ledIndex, CRGB::Black);
  }
  m_isRunning = on;
}