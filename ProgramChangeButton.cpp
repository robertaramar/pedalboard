/**
 * Implementation of a ProgramChangeButton that knows how to switch on/off the
 * drumtrack on the KRONOS.
 *
 * Author: robert.schneider@aramar.de
 */
#include "ProgramChangeButton.hpp"
#include "PedalBoard.h"

int8_t ProgramChangeButton::m_currentProgram = 0;
int8_t ProgramChangeButton::m_currentBank = 0;
int8_t ProgramChangeButton::m_currentBankLSB = 0;

ProgramChangeButton::ProgramChangeButton(ProgramChangeMode mode,
                                         int8_t fixedProgram, int8_t buttonPin,
                                         int8_t ledIndex)
    : PedalButton(buttonPin, ledIndex) {
  m_switchMode = mode;
  m_fixedProgram = fixedProgram;
  Log.verbose("ProgramChangeButton constructor" CR);
}

void ProgramChangeButton::actOnDown() {
  Log.verbose("%l ProgramChangeButton actOnDown" CR, millis());
  switchLED(m_ledIndex, CRGB::Red);
  switchProgram();
}

void ProgramChangeButton::actOnLongDown() {
  Log.verbose("%l ProgramChangeButton actOnLongDown" CR, millis());
}

void ProgramChangeButton::actOnUp() {
  Log.verbose("%l ProgramChangeButton actOnUp" CR, millis());
  switchLED(m_ledIndex, CRGB::Black);
}

void ProgramChangeButton::actOnLongUp() {
  Log.verbose("%l ProgramChangeButton actOnLongUp" CR, millis());
  switchLED(m_ledIndex, CRGB::Black);
}

void ProgramChangeButton::actOnClock() {}

void ProgramChangeButton::actOnProgramChange(byte channel, byte number) {
  Log.verbose("%l Got program change for channel %d, new program is %d" CR,
              millis(), channel, number);
  if (channel == KRONOS_CHANNEL) {
    m_currentProgram = number;
  }
}

void ProgramChangeButton::actOnControlChange(byte channel, byte number,
                                             byte value) {
  if (channel == KRONOS_CHANNEL) {
    if (number == 0) {
      m_currentBank = value;
      Log.verbose("%l Got control change for channel %d, new bank is %d" CR,
                  millis(), channel, number);
    }
    if (number == 32) {
      m_currentBankLSB = value;
      Log.verbose("%l Got control change for channel %d, new LSB bank is %d" CR,
                  millis(), channel, number);
    }
  }
}

void ProgramChangeButton::switchProgram() {
  switch (m_switchMode) {
    case ProgramUp:
      m_currentProgram++;
      break;
    case ProgramDown:
      m_currentProgram--;
      break;
    case ProgramNumber:
      m_currentProgram = m_fixedProgram;
  }

  if (m_currentProgram > 127) {
    m_currentProgram == 0;
  }
  if (m_currentProgram < 0) {
    m_currentProgram = 127;
  }

  midiS.sendControlChange(0, m_currentBank, KRONOS_CHANNEL);
  midiS.sendControlChange(32, m_currentBankLSB, KRONOS_CHANNEL);
  midiS.sendProgramChange(m_currentProgram, KRONOS_CHANNEL);

  Log.verbose("%l ProgramChangeButton switched to program %d" CR, millis(),
              m_currentProgram);
}
