/**
 * Arduino/TeensyLC program to act as a pedal controller to a MIDI keyboard.
 *
 * Author: robert.schneider@aramar.de
 */
#pragma once
#include <MIDI.h>

//#define DISABLE_LOGGING
#include <ArduinoLog.h>

#define FASTLED_INTERNAL
#include <FastLED.h>

#define BOARD_NANO 0
#define BOARD_TEENSY 1
#define LOGGING 1

#include <SoftwareSerial.h>

/**
 * Channel on which KRONOS expects incoming MIDI messages.
 */
#define KRONOS_CHANNEL 1

/**
 * Method to notify buttons of program change.
 */
void handleProgramChange(byte channel, byte number);

/**
 * Utility method to change the color of an LED (use CRGB::Black to switch off)
 */
void switchLed(int ledIndex, CRGB colorCode);
