#include "trigger_in.h"

void TriggerIn::setTrigger(bool trigger)
{
    Trigger = trigger;
}

bool TriggerIn::isTrigger() const
{
    return Trigger;
}
