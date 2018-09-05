#include "PedalButton.hpp"
#include "MomentaryButton.hpp"

MomentaryButton::MomentaryButton(int8_t buttonPin, int8_t ledIndex) : PedalButton(buttonPin, ledIndex)
{
}

void MomentaryButton::actOnDown()
{
}

void MomentaryButton::actOnLongDown()
{
}

void MomentaryButton::actOnUp()
{
}

void MomentaryButton::actOnLongUp()
{
}
