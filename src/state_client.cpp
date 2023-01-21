#include "state_client.h"

namespace ara { namespace exec {
    StateClient::StateClient() : InitialMachineStateTransitionResult(false) {}

    void StateClient::ComSetState(sm::FunctionGroupStateType) {}
    void StateClient::DiagSetState(sm::FunctionGroupStateType) {}
    void StateClient::PhmSetState(sm::FunctionGroupStateType) {}
    void StateClient::ExecSetState(sm::FunctionGroupStateType) {}

    void StateClient::GetInitialMachineStateTransitionResult() {
        InitialMachineStateTransitionResult = true;
    }
}}
