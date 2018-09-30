/**
 * Implementation of a DrumtrackButton that knows how to switch on/off the
 * drumtrack on the KRONOS.
 *
 * Author: robert.schneider@aramar.de
 */
#pragma once

#include "PedalButton.hpp"

class DrumtrackButton : public PedalButton {
 private:
  // SysEx to switch on/off drumtrack on KRONOS. Last byte is 1 to switch on, 0
  // to switch off
  static byte m_drumTrackSysEx[];

  boolean m_isRunning = false;
  int m_currentClock = 0;
  CRGB::HTMLColorCode m_currentColorCode;

 public:
  DrumtrackButton(int8_t buttonPin, int8_t ledIndex);
  void actOnDown();
  void actOnLongDown();
  void actOnUp();
  void actOnLongUp();
  void actOnClock();

 private:
  void DrumtrackButton::switchDrumTrack(boolean on);
};