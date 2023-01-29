#ifndef AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_H
#define AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_H
/** @file trigger_in.h
 * @brief Trigger in interface. */

#include "sm_types.h"

namespace ara::com {

/** @brief Fills [SWS_SM_91007] */
    class TriggerIn {
    public:
        [[nodiscard]] bool IsTrigger() const;
        [[nodiscard]] sm::FunctionGroupStateType GetDesiredState() const;

        void SetTrigger(sm::FunctionGroupStateType);
        void DiscardTrigger();

    private:
        sm::TriggerType trigger;
    };
}
#endif //AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_H
