#include "trigger_out.h"

namespace ara::com {
    
    sm::FunctionGroupStateType TriggerOut::GetNotifier() const {
        return notifier;
    }

    void TriggerOut::SetNotifier(sm::FunctionGroupStateType newNotifier) {
        notifier = newNotifier;
    }

}
