#include "state_client.h"

namespace ara::exec {

    ExecErrc StateClient::SmSetState(sm::FunctionGroupStateType requestedState) {
        requestedSMState = requestedState;
        return ExecErrc::kSuccess;
    }

    void StateClient::undefinedStateCallback() {
        // TBD
    }

    sm::FunctionGroupStateType StateClient::SmGetState() {
        return requestedSMState;
    }
}