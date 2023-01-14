#include "trigger_in.h"

namespace ara { namespace com {

    void TriggerIn::setTrigger(bool trigger) {
        Trigger = trigger;
    }

    bool TriggerIn::isTrigger() const {
        return Trigger;
    }
}}
