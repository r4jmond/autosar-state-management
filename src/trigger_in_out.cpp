#include "trigger_in_out.h"

namespace ara { namespace com {

    bool TriggerInOut::isNotifier() const {
        return notifier;
    }

    void TriggerInOut::setNotifier(bool notifier) {
        TriggerInOut::notifier = notifier;
    }

    bool TriggerInOut::isTrigger() const {
        return trigger;
    }

    void TriggerInOut::setTrigger(bool trigger) {
        TriggerInOut::trigger = trigger;
    }
}}
