#include "state_client.h"

namespace ara::exec {

    void StateClient::SmSetState(sm::FunctionGroupStateType requestedState) {
        if (sm::FunctionGroupStateType::Off == requestedState) {
            requestedSMState = ara::sm::SMStateType::Off;
        }
        else if (sm::FunctionGroupStateType::On == requestedState) {
            requestedSMState = ara::sm::SMStateType::On;
        }
        else {
            undefinedStateCallback();
        }
    }

    void StateClient::undefinedStateCallback() {
        // TBD
    }
}