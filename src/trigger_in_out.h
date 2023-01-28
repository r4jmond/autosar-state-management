#ifndef AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_OUT_H
#define AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_OUT_H
/** @file trigger_in_out.h
 * @brief Trigger in_out interface. */

#include "sm_types.h"

namespace ara::com {

    /** @brief Fills [SWS_SM_91009] */
    class TriggerInOut {
    public:
        [[nodiscard]] sm::TriggerInOutNotifierType GetNotifier() const;
        void SetTrigger(sm::SMStateType);

        void SetNotifier(sm::ErrorType result, sm::SMStateType currentSMState);
        [[nodiscard]] bool IsTrigger() const;
        [[nodiscard]] sm::SMStateType GetDesiredState() const;
        void DiscardTrigger();

    private:
        sm::TriggerInOutNotifierType notifier;
        sm::TriggerType trigger;
    };
}
#endif //AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_OUT_H
