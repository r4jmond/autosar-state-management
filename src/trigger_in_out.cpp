#include "trigger_in_out.h"

namespace ara::com {

    sm::TriggerInOutNotifierType TriggerInOut::GetNotifier() const {
        return notifier;
    }

    void TriggerInOut::SetTrigger(sm::FunctionGroupStateType desiredSMState) {
        trigger.desiredSMState = desiredSMState;
        trigger.isNewTrigger = true;
    }

    void TriggerInOut::DiscardTrigger() {
        trigger.isNewTrigger = false;
    }

    void TriggerInOut::SetNotifier(sm::ErrorType result, sm::FunctionGroupStateType currentSMState) {
        notifier.result = result;
        notifier.currentSMState = currentSMState;
    }

    bool TriggerInOut::IsTrigger() const {
        return trigger.isNewTrigger;
    }

    sm::FunctionGroupStateType TriggerInOut::GetDesiredState() const {
        return trigger.desiredSMState;
    }
}
