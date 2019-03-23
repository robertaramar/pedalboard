/**
 * Implementation of a MomentaryButton that knows what to do on what kind of
 * press.
 *
 * Author: robert.schneider@aramar.de
 */
#include "MomentaryButton.hpp"
#include "PedalBoard.h"

MomentaryButton::MomentaryButton(int8_t buttonPin, int8_t ledIndex)
    : PedalButton(buttonPin, ledIndex) {
  Log.verbose("MomentaryButton constructor" CR);
}

void MomentaryButton::actOnDown() {
  Log.verbose("%l MomentaryButton %d actOnDown" CR, millis(), m_ledIndex);
  switchLed(m_ledIndex, CRGB::Red);
  usbMIDI.sendNoteOn(50 + m_ledIndex, 71, 1);
}

void MomentaryButton::actOnLongDown() {
  Log.verbose("%l MomentaryButton %d actOnLongDown" CR, millis(), m_ledIndex);
  switchLed(m_ledIndex, CRGB::Green);
}

void MomentaryButton::actOnUp() {
  Log.verbose("%l MomentaryButton %d actOnUp" CR, millis(), m_ledIndex);
  switchLed(m_ledIndex, CRGB::Black);
  usbMIDI.sendNoteOff(50 + m_ledIndex, 71, 1);
}

void MomentaryButton::actOnLongUp() {
  Log.verbose("%l MomentaryButton %d actOnLongUp" CR, millis(), m_ledIndex);
  switchLed(m_ledIndex, CRGB::Black);
  usbMIDI.sendNoteOff(50 + m_ledIndex, 71, 1);
}

void MomentaryButton::actOnClock() {}

void MomentaryButton::actOnProgramChange(byte channel, byte number) {}

void MomentaryButton::actOnControlChange(byte channel, byte number, byte value) {}