#include "diagnostic_reset.h"

namespace ara::sm {

    bool DiagnosticReset::TryGetDiagnosticResetMsg(std::string *msg) {
        if (msgToProcesses) {
            *msg = this->diagnosticResetMsg;
            msgToProcesses = false;
            return true;
        }
        else {
            return false;
        }
    }

    bool DiagnosticReset::TryGetDiagnosticResetMsgResponse(DiagnosticResetRespMsg *respondMsg) {
        if (msgToStateMachine) {
            *respondMsg = this->processResponse;
            msgToStateMachine = false;
            return true;
        }
        else {
            return false;
        }
    }

    void DiagnosticReset::Event(DiagnosticResetRespMsg respondMsg) {
        this->processResponse = respondMsg;
        this->msgToStateMachine = true;
    }


    bool DiagnosticReset::Message(std::string msg) {
        if (msg != DiagnosticResetMsg::SoftReset) {
            return false;
        }
        else {
            this->diagnosticResetMsg = msg;
            this->msgToProcesses = true;
            return true;
        }
    }
}