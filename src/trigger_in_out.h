#ifndef AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_OUT_H
#define AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_OUT_H
/** @file trigger_in_out.h
 * @brief Trigger in_out interface. */

#include "sm_types.h"

namespace ara::com {

    /** @brief Fills [SWS_SM_91009] */
    class TriggerInOut {
    public:
        sm::TriggerInOutNotifierType GetTransitionResult() const;
        void SetSMState(sm::SMStateType);

        void SetTransitionResult(sm::ErrorType, sm::SMStateType);
        bool IsTrigger() const;
        void DiscardTrigger();

    private:
        sm::TriggerInOutNotifierType notifier;
        sm::SMStateType trigger;

        sm::ErrorType transitionResult;
        bool isTrigger = false;
    };
}
#endif //AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_OUT_H
