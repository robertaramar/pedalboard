/**
 * Implementation of a ProgramChangeButton that knows how to switch on/off the
 * drumtrack on the KRONOS.
 *
 * Author: robert.schneider@aramar.de
 */
#include "ProgramChangeButton.hpp"
#include "PedalBoard.h"

int8_t ProgramChangeButton::m_currentProgram = 0;
int8_t ProgramChangeButton::m_currentBank = 1;
int8_t ProgramChangeButton::m_currentBankLSB = 0;

ProgramChangeButton::ProgramChangeButton(ProgramChangeMode mode, int8_t fixedProgram,
                                         int8_t buttonPin, int8_t ledIndex)
    : PedalButton(buttonPin, ledIndex) {
  m_switchMode = mode;
  m_fixedProgram = fixedProgram;
  Log.trace("ProgramChangeButton constructor" CR);
}

void ProgramChangeButton::actOnDown() {
  Log.trace("%l ProgramChangeButton actOnDown" CR, millis());
  switchLed(m_ledIndex, CRGB::Red);
  switchProgram();
}

void ProgramChangeButton::actOnLongDown() {
  Log.trace("%l ProgramChangeButton actOnLongDown" CR, millis());
}

void ProgramChangeButton::actOnUp() {
  Log.trace("%l ProgramChangeButton actOnUp" CR, millis());
  switchLed(m_ledIndex, CRGB::Black);
}

void ProgramChangeButton::actOnLongUp() {
  Log.trace("%l ProgramChangeButton actOnLongUp" CR, millis());
  switchLed(m_ledIndex, CRGB::Black);
}

void ProgramChangeButton::actOnClock() {}

void ProgramChangeButton::actOnProgramChange(byte channel, byte number) {
  Log.trace("%l Got program change for channel %d, new program is %d" CR, millis(), channel,
            number);
  if (channel == KRONOS_CHANNEL) {
    m_currentProgram = number;
  }
}

void ProgramChangeButton::actOnControlChange(byte channel, byte number, byte value) {
  if (channel == KRONOS_CHANNEL) {
    Log.trace("%l %d, CC Bank selection (%d), value %d" CR, millis(), channel, number, value);
    if (number == 0) {
      m_currentBank = value;
      Log.trace("%l Got control change for channel %d, new bank is %d" CR, millis(), channel,
                value);
    }
    if (number == 32) {
      m_currentBankLSB = value;
      Log.trace("%l Got control change for channel %d, new LSB bank is %d" CR, millis(), channel,
                value);
    }
  }
}

void ProgramChangeButton::switchProgram() {
  switch (m_switchMode) {
  case ProgramUp:
    m_currentProgram++;
    if (m_currentProgram < 0) {
      m_currentProgram = 0;
    }
    break;
  case ProgramDown:
    m_currentProgram--;
    if (m_currentProgram < 0) {
      m_currentProgram = 127;
    }
    break;
  case ProgramNumber:
    m_currentProgram = m_fixedProgram;
  }

  if (m_currentProgram < 0 || m_currentProgram > 127) {
    m_currentProgram = 0;
  }

  usbMIDI.sendControlChange(0, m_currentBank, KRONOS_CHANNEL);
  usbMIDI.sendControlChange(32, m_currentBankLSB, KRONOS_CHANNEL);
  usbMIDI.sendProgramChange(m_currentProgram, KRONOS_CHANNEL);

  // Notify all other buttons of the program change as the KRONOS does not reflect that back to the
  // MIDI interface
  handleProgramChange(KRONOS_CHANNEL, m_currentProgram);

  Log.trace("%l ProgramChangeButton switched to program %d" CR, millis(), m_currentProgram);
}
