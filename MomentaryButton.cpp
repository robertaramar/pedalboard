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
  Log.verbose("%l MomentaryButton actOnDown" CR, millis());
  switchLed(m_ledIndex, CRGB::Red);
  midiS.sendNoteOn(50, 71, 1);
}

void MomentaryButton::actOnLongDown() {
  Log.verbose("%l MomentaryButton actOnLongDown" CR, millis());
  switchLed(m_ledIndex, CRGB::Green);
}

void MomentaryButton::actOnUp() {
  Log.verbose("%l MomentaryButton actOnUp" CR, millis());
  switchLed(m_ledIndex, CRGB::Blue);
  midiS.sendNoteOff(50, 71, 1);
}

void MomentaryButton::actOnLongUp() {
  Log.verbose("%l MomentaryButton actOnLongUp" CR, millis());
  switchLed(m_ledIndex, CRGB::Yellow);
}

void MomentaryButton::actOnClock() {}

void MomentaryButton::actOnProgramChange(byte channel, byte number) {}

void MomentaryButton::actOnControlChange(byte channel, byte number,
                                         byte value) {}