//
// Created by r4jmund on 29.12.22.
//

#include "trigger_out.h"

bool TriggerOut::isNotifier() const
{
    return notifier;
}

void TriggerOut::setNotifier(bool notifier)
{
    TriggerOut::notifier = notifier;
}
