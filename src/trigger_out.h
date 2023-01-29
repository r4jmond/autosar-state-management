#ifndef AUTOSAR_STATE_MANAGEMENT_TRIGGER_OUT_H
#define AUTOSAR_STATE_MANAGEMENT_TRIGGER_OUT_H
/** @file trigger_out.h
 * @brief Trigger out interface. */

#include "sm_types.h"

namespace ara::com {

/** @brief Fills [SWS_SM_91008] */
    class TriggerOut {
    public:
        [[nodiscard]] sm::SMStateType GetNotifier() const;

        void SetNotifier(sm::SMStateType);

    private:
        sm::SMStateType notifier;
    };
}
#endif //AUTOSAR_STATE_MANAGEMENT_TRIGGER_OUT_H
