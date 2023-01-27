#include "trigger_in_out.h"

namespace ara::com {

    sm::TriggerInOutNotifierType TriggerInOut::GetTransitionResult() const {
        return notifier;
    }

    void TriggerInOut::SetSMState(sm::SMStateType desiredSMState) {
        trigger = desiredSMState;
        isTrigger = true;
    }

    void TriggerInOut::DiscardTrigger() {
        isTrigger = false;
    }

    void TriggerInOut::SetTransitionResult(sm::ErrorType result, sm::SMStateType currentSMState) {
        notifier.result = result;
        notifier.currentSMState = currentSMState;
    }

    bool TriggerInOut::IsTrigger() const {
        return isTrigger;
    }
}
