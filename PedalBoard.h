/**
 * Arduino/TeensyLC program to act as a pedal controller to a MIDI keyboard.
 *
 * Author: robert.schneider@aramar.de
 */
#pragma once

/**
 * MIDI object to send/receive MIDI data.
 */
extern midi::MidiInterface<SoftwareSerial> midiS;

/**
 * Utility method to change the color of an LED (use CRGB::Black to switch off)
 */
void switchLED(int ledIndex, CRGB::HTMLColorCode colorCode);
