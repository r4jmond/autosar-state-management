#ifndef AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_H
#define AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_H

namespace ara { namespace com {

/** @brief Fills [SWS_SM_91008] */
    class TriggerIn {
    public:
        bool IsTrigger() const;

        void SetTrigger(bool trigger);

    private:
        bool trigger;
    };
}}
#endif //AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_H
