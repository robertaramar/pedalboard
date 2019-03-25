/**
 * Implementation of a AnalogControl that knows what to do on what kind of press.
 *
 * Author: robert.schneider@aramar.de
 */
#include "PedalBoard.h"

#pragma once

class AnalogControl {
protected:
  int8_t m_oldValue; // old value to compare and, hence, save MIDI outs

public:
  AnalogControl();
  void init();
  void loop();
};