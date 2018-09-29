#include <ArduinoLog.h>
#include <FastLED.h>
#include "PedalButton.hpp"
#include "MomentaryButton.hpp"

MomentaryButton::MomentaryButton(int8_t buttonPin, int8_t ledIndex, CRGB *leds) : PedalButton(buttonPin, ledIndex, leds)
{
    Log.verbose("MomentaryButton constructor" CR);
}

void MomentaryButton::actOnDown()
{
    Log.verbose("%l MomentaryButton actOnDown" CR, millis());
    m_leds[m_ledIndex] = CRGB::Red;
    FastLED.show();
}

void MomentaryButton::actOnLongDown()
{
    Log.verbose("%l MomentaryButton actOnLongDown" CR, millis());
    m_leds[m_ledIndex] = CRGB::Green;
    FastLED.show();
}

void MomentaryButton::actOnUp()
{
    Log.verbose("%l MomentaryButton actOnUp" CR, millis());
    m_leds[m_ledIndex] = CRGB::Blue;
    FastLED.show();
}

void MomentaryButton::actOnLongUp()
{
    Log.verbose("%l MomentaryButton actOnLongUp" CR, millis());
    m_leds[m_ledIndex] = CRGB::Yellow;
    FastLED.show();
}
