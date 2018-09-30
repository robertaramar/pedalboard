/**
 * Implementation of a MomentaryButton that knows what to do on what kind of
 * press.
 *
 * Author: robert.schneider@aramar.de
 */
#pragma once

#include "PedalButton.hpp"
class MomentaryButton : public PedalButton {
 public:
  MomentaryButton(int8_t buttonPin, int8_t ledIndex);
  void actOnDown();
  void actOnLongDown();
  void actOnUp();
  void actOnLongUp();
};