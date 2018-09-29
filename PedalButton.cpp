/**
 * Implementation of a PedalButton that knows what to do on what kind of press.
 * 
 * Author: robert.schneider@aramar.de
 */
#include <FastLED.h>
#include <ArduinoLog.h>
#include "PedalButton.hpp"

#define BOUNCE_INTERVAL 5              // ms
#define LONG_BUTTON_PRESS_TIMEOUT 2000 // 2 seconds

PedalButton::PedalButton(int8_t buttonPin, int8_t ledIndex, CRGB *leds)
{
    Log.verbose("Pedalbutton constructor"CR);
    m_buttonPin = buttonPin;
    m_ledIndex = ledIndex;
    m_leds = leds;
}

/**
     * Initialize this button by setting the pinmode and creating a debouncer
     */
void PedalButton::init()
{
    Log.verbose("Pedalbutton init"CR);
    pinMode(m_buttonPin, INPUT_PULLUP);
    m_debouncer = Bounce();
    m_debouncer.attach(m_buttonPin);
    m_debouncer.interval(BOUNCE_INTERVAL);
}

/**
     * Read the button state and see whether any action is required
     */
void PedalButton::loop()
{
    m_debouncer.update();
    if (m_debouncer.fell())
    {
        if (m_buttonState == Up || m_buttonState == LongUp)
        {
            actOnDown();
        }
        m_buttonState = Down;
    }
    else if (m_debouncer.rose())
    {
        if (m_buttonState == Down)
        {
            actOnUp();
            m_buttonState = Up;
        }
        else if (m_buttonState == LongDown)
        {
            actOnLongUp();
            m_buttonState = LongUp;
        }
    }
    else
    {
        int state = m_debouncer.read();
        if (state == LOW && m_buttonState != LongDown)
        {
            if (m_debouncer.duration() >= LONG_BUTTON_PRESS_TIMEOUT)
            {
                actOnLongDown();
                m_buttonState = LongDown;
            }
        }
    }
}