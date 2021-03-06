/**
 * Implementation of a KarmaSceneButton that knows how to switch on/off the
 * drumtrack on the KRONOS.
 *
 * Author: robert.schneider@aramar.de
 */
#pragma once
#include "PedalBoard.h"
#include "PedalButton.hpp"

enum KarmaSwitchMode { KarmaUp, KarmaDown, KarmaScene };

class KarmaSceneButton : public PedalButton {
 private:
  // SysEx to switch to a different Karma scene. Last byte holds the Karma scene number (0 - 7).
  static byte m_karmaSwitchSysEx[];
  // LED colors for different Karma scenes.
  static CRGB::HTMLColorCode m_colorCodes[];
  // Current scene needs to be static, in order to sync up and down buttons.
  static int8_t m_currentScene;

  KarmaSwitchMode m_switchMode = KarmaSwitchMode::KarmaUp;
  int8_t m_fixedScene = 0;

 public:
  KarmaSceneButton(KarmaSwitchMode mode, int8_t fixedScene, int8_t buttonPin, int8_t ledIndex);
  void actOnDown();
  void actOnLongDown();
  void actOnUp();
  void actOnLongUp();
  void actOnClock();
  void actOnProgramChange(byte channel, byte number);
  void actOnControlChange(byte channel, byte number, byte value);

 private:
  void switchKarmaScene();
};