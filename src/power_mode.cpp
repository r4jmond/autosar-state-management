#include "power_mode.h"

namespace ara::com {

    bool PowerMode::tryGetPowerMsg(std::string *msg) {
        if (msgToProcesses) {
            *msg = this->powerModeMsg;
            msgToProcesses = false;
            return true;
        } else {
            return false;
        }
    }

    bool PowerMode::tryGetPowerMsgResponse(sm::PowerModeRespMsg *respondMsg) {
        if (msgToStateMachine) {
            *respondMsg = this->processResponse;
            msgToStateMachine = false;
            return true;
        } else {
            return false;
        }
    }

    void PowerMode::event(sm::PowerModeRespMsg respondMsg) {
        this->processResponse = respondMsg;
        this->msgToStateMachine = true;
    }


    bool PowerMode::message(std::string msg) {
        if ((msg != sm::PowerModeMsg::On) && (msg != sm::PowerModeMsg::Off) && (msg != sm::PowerModeMsg::Suspend)) {
            return false;
        } else {
            this->powerModeMsg = msg;
            this->msgToProcesses = true;
            return true;
        }
    }
}