#include "trigger_in.h"

namespace ara { namespace com {

    void TriggerIn::SetTrigger(bool newTrigger) {
        trigger = newTrigger;
    }

    bool TriggerIn::IsTrigger() const {
        return trigger;
    }
}}
