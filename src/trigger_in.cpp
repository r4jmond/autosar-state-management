#include "trigger_in.h"

namespace ara::com {

    void TriggerIn::SetTrigger(sm::FunctionGroupStateType newTrigger) {
        trigger.desiredSMState = newTrigger;
        trigger.isNewTrigger = true;
    }

    bool TriggerIn::IsTrigger() const {
        return trigger.isNewTrigger;
    }

    void TriggerIn::DiscardTrigger() {
        trigger.isNewTrigger = false;
    }

    sm::FunctionGroupStateType TriggerIn::GetDesiredState() const {
        return trigger.desiredSMState;
    }
}
