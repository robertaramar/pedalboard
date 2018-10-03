/**
 * Implementation of a ProgramChangeButton that knows how to switch on/off the
 * drumtrack on the KRONOS.
 *
 * Author: robert.schneider@aramar.de
 */
#pragma once

#include "PedalBoard.h"
#include "PedalButton.hpp"

enum ProgramChangeMode { ProgramUp, ProgramDown, ProgramNumber };

class ProgramChangeButton : public PedalButton {
 private:
  // Current scene needs to be static, in order to sync up and down buttons.
  static int8_t m_currentProgram;
  static int8_t m_currentBank;
  static int8_t m_currentBankLSB;

  ProgramChangeMode m_switchMode = ProgramChangeMode::ProgramUp;
  int8_t m_fixedProgram = 0;

 public:
  ProgramChangeButton(ProgramChangeMode mode, int8_t fixedProgram, int8_t buttonPin, int8_t ledIndex);
  void actOnDown();
  void actOnLongDown();
  void actOnUp();
  void actOnLongUp();
  void actOnClock();
  void actOnProgramChange(byte channel, byte number);
  void actOnControlChange(byte channel, byte number, byte value);

 private:
  void switchProgram();
};