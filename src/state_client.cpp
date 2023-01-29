#include "state_client.h"

namespace ara::exec {

    ExecErrc StateClient::SmSetState(sm::FunctionGroupStateType requestedState) {
        if ((requestedState == sm::FunctionGroupStateType::On) || (requestedState == sm::FunctionGroupStateType::Off)) {
            requestedSMState = requestedState;
            return ExecErrc::kSuccess;
        } else {
            undefinedStateCallback();
            return ExecErrc::kGeneralError;
        }
    }

    sm::FunctionGroupStateType StateClient::SmGetState() {
        return requestedSMState;
    }
}