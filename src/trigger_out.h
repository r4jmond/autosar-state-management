#ifndef AUTOSAR_STATE_MANAGEMENT_TRIGGER_OUT_H
#define AUTOSAR_STATE_MANAGEMENT_TRIGGER_OUT_H
/** @file trigger_out.h
 * @brief Trigger out interface. */

#include "sm_types.h"

namespace ara::com {

/** @brief Fills [SWS_SM_91008] */
    class TriggerOut {
    public:
        TriggerOut() : notifier{sm::FunctionGroupStateType::Off} {}

        [[nodiscard]] sm::FunctionGroupStateType GetNotifier() const;

        void SetNotifier(sm::FunctionGroupStateType);

    private:
        sm::FunctionGroupStateType notifier;
    };
}
#endif //AUTOSAR_STATE_MANAGEMENT_TRIGGER_OUT_H
