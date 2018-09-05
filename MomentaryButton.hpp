#pragma once

class MomentaryButton : public PedalButton
{
public:
    MomentaryButton(int8_t buttonPin, int8_t ledIndex);
    void actOnDown();
    void actOnLongDown();
    void actOnUp();
    void actOnLongUp();
};