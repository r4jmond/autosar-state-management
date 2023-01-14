#include "trigger_out.h"

namespace ara { namespace com {

    bool TriggerOut::IsNotifier() const {
        return notifier;
    }

    void TriggerOut::SetNotifier(bool newNotifier) {
        TriggerOut::notifier = newNotifier;
    }

}}