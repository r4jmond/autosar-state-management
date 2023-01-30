#include "power_mode.h"

namespace ara::com {

    bool PowerMode::TryGetPowerMsg(std::string *msg) {
        if (msgToProcesses) {
            *msg = this->powerModeMsg;
            msgToProcesses = false;
            return true;
        }
        else {
            return false;
        }
    }

    bool PowerMode::TryGetPowerMsgResponse(sm::PowerModeRespMsg *respondMsg) {
        if (msgToStateMachine) {
            *respondMsg = this->processResponse;
            msgToStateMachine = false;
            return true;
        }
        else {
            return false;
        }
    }

    void PowerMode::Event(sm::PowerModeRespMsg respondMsg) {
        this->processResponse = respondMsg;
        this->msgToStateMachine = true;
    }


    bool PowerMode::Message(std::string msg) {
        if ((msg != sm::PowerModeMsg::On) && (msg != sm::PowerModeMsg::Off) && (msg != sm::PowerModeMsg::Suspend)) {
            return false;
        }
        else {
            this->powerModeMsg = msg;
            this->msgToProcesses = true;
            return true;
        }
    }
}