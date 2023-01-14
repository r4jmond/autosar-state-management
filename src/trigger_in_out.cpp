#include "trigger_in_out.h"

namespace ara { namespace com {

    bool TriggerInOut::IsNotifier() const {
        return notifier;
    }

    void TriggerInOut::SetNotifier(bool newNotifier) {
        TriggerInOut::notifier = newNotifier;
    }

    bool TriggerInOut::IsTrigger() const {
        return trigger;
    }

    void TriggerInOut::SetTrigger(bool newTrigger) {
        TriggerInOut::trigger = newTrigger;
    }
}}
