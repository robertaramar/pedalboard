/**
 * Implementation of a PedalButton that knows what to do on what kind of press.
 * 
 * Author: robert.schneider@aramar.de
 */
#include "PedalButton.hpp"

#define BOUNCE_INTERVAL 5              // ms
#define LONG_BUTTON_PRESS_TIMEOUT 2000 // 2 seconds

PedalButton::PedalButton(int8_t buttonPin, int8_t ledIndex)
{
    m_buttonPin = buttonPin;
    m_ledIndex = ledIndex;
}

/**
     * Initialize this button by setting the pinmode and creating a debouncer
     */
void PedalButton::init()
{
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
        if (m_buttonState == ButtonState.Up || m_buttonState == ButtonState.LongUp)
        {
            pedalButton.actOnDown();
        }
        m_buttonState = ButtonState.Down;
    }
    else if (m_debouncer.rose())
    {
        if (m_buttonState == ButtonState.Down)
        {
            pedalButton.actOnUp();
            m_buttonState = ButtonState.Up;
        }
        else if (m_buttonState == ButtonState.LongDown)
        {
            pedalButton.actOnLongUp();
            m_buttonState = ButtonState.LongUp;
        }
    }
    else
    {
        int state = m_debouncer.read();
        if (state == LOW && m_buttonState != ButtonState.LongDown)
        {
            if (m_debouncer.duration() >= LONG_BUTTON_PRESS_TIMEOUT)
            {
                pedalButton.actOnLongDown();
                m_buttonState = ButtonState.LongDown;
            }
        }
    }
}