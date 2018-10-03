/**
 * Implementation of a PedalButton that knows what to do on what kind of press.
 *
 * Author: robert.schneider@aramar.de
 */
#include <Bounce2.h>

#pragma once

enum ButtonState {
  Up = 0x00,        // button had been pressed
  Down = 0x01,      // button had been release from a short press
  LongDown = 0x02,  // button is down for a certain time
  LongUp = 0x03     // button had been released after a certain time
};

class PedalButton {
 protected:
  int8_t m_buttonPin;  // physical pin of this button
  int8_t m_ledIndex;   // index into the LED array for this button

  Bounce m_debouncer;         // Bounce object to manage button
  ButtonState m_buttonState;  // Current button state

 public:
  PedalButton(int8_t buttonPin, int8_t ledIndex);
  void init();
  void loop();
  virtual void actOnDown() = 0;
  virtual void actOnLongDown() = 0;
  virtual void actOnUp() = 0;
  virtual void actOnLongUp() = 0;
  virtual void actOnClock() = 0;
};