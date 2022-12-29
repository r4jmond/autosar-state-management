#ifndef AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_OUT_H
#define AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_OUT_H

class TriggerInOut
{
private:
    bool notifier;
public:
    bool isNotifier() const;

    void setNotifier(bool notifier);

private:
    bool trigger;
public:
    bool isTrigger() const;

    void setTrigger(bool trigger);
};


#endif //AUTOSAR_STATE_MANAGEMENT_TRIGGER_IN_OUT_H
