#include "trigger_in.h"

namespace ara::com {

    void TriggerIn::SetTrigger(sm::SMStateType newTrigger) {
        trigger = newTrigger;
        isTrigger = true;
    }

    bool TriggerIn::IsTrigger() const {
        return isTrigger;
    }

    void TriggerIn::DiscardTrigger() {
        isTrigger = false;
    }

    sm::SMStateType TriggerIn::GetDesiredState() const {
        return trigger;
    }
}
