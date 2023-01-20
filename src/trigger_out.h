#ifndef AUTOSAR_STATE_MANAGEMENT_TRIGGER_OUT_H
#define AUTOSAR_STATE_MANAGEMENT_TRIGGER_OUT_H
/** @file trigger_out.h
 * @brief Trigger out interface. */

namespace ara { namespace com {

/** @brief Fills [SWS_SM_91008] */
    class TriggerOut {
    public:
        bool IsNotifier() const;

        void SetNotifier(bool newNotifier);

    private:
        bool notifier;
    };
}}
#endif //AUTOSAR_STATE_MANAGEMENT_TRIGGER_OUT_H
