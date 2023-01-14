#include "trigger_out.h"

namespace ara { namespace com {

    bool TriggerOut::isNotifier() const {
        return notifier;
    }

    void TriggerOut::setNotifier(bool notifier) {
        TriggerOut::notifier = notifier;
    }

}}