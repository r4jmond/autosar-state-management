#ifndef AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_H
#define AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_H

/** @brief Fills [SWS_SM_91001] */
class TriggerIn
{
private:
    bool Trigger;
public:
    bool isTrigger() const;
    void setTrigger(bool trigger);
};

#endif //AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_H
