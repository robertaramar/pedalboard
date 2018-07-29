/**
 * Implementation of a PedalButton that knows what to do on what kind of press.
 * 
 * Author: robert.schneider@aramar.de
 */

typedef void (*ButtonMethod)();

class PedalButton
{

    int8_t ledIndex; // index into the LED array for this button

    ButtonMethod actOnDown;     // when button is pressed
    ButtonMethod actOnUp;       // when button is released
    ButtonMethod actOnLongDown; // when button is pressed longer than 5s
    ButtonMethod actOnLongUp;   // when button is released after >= 5s

  public:
    PedalButton();
    PedalButton(int8_t ledIndex, ButtonMethod actOnDown, ButtonMethod actOnUp, ButtonMethod actOnLongDown, ButtonMethod actOnLongUp);
    void handleButtonState();
};