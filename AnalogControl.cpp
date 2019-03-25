/**
 * Implementation of a AnalogControl that knows what to do on what kind of press.
 *
 * Author: robert.schneider@aramar.de
 */
#include "AnalogControl.hpp"
#include "PedalBoard.h"
#include <ResponsiveAnalogRead.h>

/**
 * Analog input pin for the volume pedal.
 */
#define VOLUME_PEDAL A3
ResponsiveAnalogRead analog(VOLUME_PEDAL, true);

AnalogControl::AnalogControl() {
  Log.verbose("AnalogControl constructor" CR);
  m_oldValue = -1;
}

/**
 * Initialize this button by setting the pinmode and creating a debouncer
 */
void AnalogControl::init() {
  Log.verbose("AnalogControl init" CR);
  analog.setAnalogResolution(127);
  analogReadResolution(7);
  m_oldValue = analogRead(VOLUME_PEDAL); // always divide by 8 to make 0 - 1023 ==> 0 - 127 (MIDI)
}

/**
 * Read the button state and see whether any action is required
 */
void AnalogControl::loop() {
  analog.update();
  uint16_t newValue = analog.getValue();
  if (newValue != m_oldValue) {
    Log.verbose("AnalogControl sending volume %d" CR, newValue);
    usbMIDI.sendControlChange(midi::ChannelVolume, newValue, KRONOS_CHANNEL);
    m_oldValue = newValue;
  }
}
