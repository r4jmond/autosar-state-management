#ifndef AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_OUT_H
#define AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_OUT_H
/** @file trigger_in_out.h
 * @brief Trigger in_out interface. */

namespace ara { namespace com {

    /** @brief Fills [SWS_SM_91009] */
    class TriggerInOut {
    public:
        bool IsNotifier() const;

        void SetNotifier(bool newNotifier);

        bool IsTrigger() const;

        void SetTrigger(bool newTrigger);

    private:
        bool notifier;
        bool trigger;
    };
}}
#endif //AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_OUT_H
