#ifndef AUTOSAR_STATE_MANAGEMENT_TRIGGER_OUT_H
#define AUTOSAR_STATE_MANAGEMENT_TRIGGER_OUT_H


class TriggerOut
{
private:
    bool notifier;
public:
    bool isNotifier() const;

    void setNotifier(bool notifier);
};


#endif //AUTOSAR_STATE_MANAGEMENT_TRIGGER_OUT_H
