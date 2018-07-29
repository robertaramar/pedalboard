/**
 * Implementation of a PedalButton that knows what to do on what kind of press.
 * 
 * Author: robert.schneider@aramar.de
 */

#include "PedalButton.h"

class PedalButton
{

    int8_t ledIndex; // index into the LED array for this button

    buttonMethod actOnDown;     // when button is pressed
    buttonMethod actOnUp;       // when button is released
    buttonMethod actOnLongDown; // when button is pressed longer than 5s
    buttonMethod actOnLongUp;   // when button is released after >= 5s

  public:
    PedalButton();
    PedalButton(int8_t ledIndex, ButtonMethod actOnDown, ButtonMethod actOnUp, ButtonMethod actOnLongDown, ButtonMethod actOnLongUp)
    {
        this.ledIndex = ledIndex;
        this.actOnDown = actOnDown;
        this.actOnUp = actOnUp;
        this.actOnLongDown = actOnLongDown;
        this.actOnLongUp = actOnLongUp;
    }

    void handleButtonState() {

    }
}