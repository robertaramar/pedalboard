/**
 * Arduino/TeensyLC program to act as a pedal controller to a MIDI keyboard.
 *
 * Author: robert.schneider@aramar.de
 */
#pragma once
#include <MIDI.h>
#define FASTLED_INTERNAL
#define DISABLE_LOGGING
#include <ArduinoLog.h>
#include <FastLED.h>
#include <SoftwareSerial.h>

/**
 * Channel on which KRONOS expects incoming MIDI messages.
 */
#define KRONOS_CHANNEL 1

/**
 * MIDI object to send/receive MIDI data.
 */
extern midi::MidiInterface<HardwareSerial> midiS;

/**
 * Utility method to change the color of an LED (use CRGB::Black to switch off)
 */
void switchLED(int ledIndex, CRGB colorCode);
