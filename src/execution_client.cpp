#include "execution_client.h"

namespace ara::exec {
    void ExecutionClient::ReportApplicationState(sm::SMStateType state) {
        currentState = state;
    }

    sm::SMStateType ExecutionClient::GetApplicationState() {
        return currentState;
    }
}
