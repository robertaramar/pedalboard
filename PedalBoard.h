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
 * Switch on/off software serial to use/not use serial console
 */
#define SOFTWARE_SERIAL 1

/**
 * MIDI object to send/receive MIDI data.
 */
#if SOFTWARE_SERIAL
extern midi::MidiInterface<SoftwareSerial> midiS;
#else
extern midi::MidiInterface<HardwareSerial> midiS;
#endif

/**
 * Utility method to change the color of an LED (use CRGB::Black to switch off)
 */
void switchLED(int ledIndex, CRGB colorCode);
