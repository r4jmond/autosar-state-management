#include "trigger_out.h"

namespace ara::com {

    sm::SMStateType TriggerOut::GetNotifier() const {
        return notifier;
    }

    void TriggerOut::SetNotifier(sm::SMStateType newNotifier) {
        notifier = newNotifier;
    }

}
