#include "state_management.h"
#include <iostream>

namespace ara::sm {

    void StateManagement::Work() {
        std::cout << "Starting work" << std::endl;
        while (!killFlag) {
            Worker();
        }
        std::cout << "Finished work" << std::endl;
    }

    void StateManagement::Worker() {
        if (myUpdateRequest.IsResetRequest()) {
            myUpdateRequest.SetResetAccepted(true);
            myUpdateRequest.SetResetRequest(false);
        } else {
            //don't reset??
        }

        if (triggerIn.IsTrigger()) {
            SMStateType requestedSMState = triggerInOut.GetDesiredState();
            FunctionGroupStateType newSMState = FunctionGroupStateType::Shutdown;
            if (requestedSMState == SMStateType::On) {
                newSMState = FunctionGroupStateType::On;
            } else if (requestedSMState == SMStateType::Off) {
                newSMState = FunctionGroupStateType::Off;
            }
            stateClient->SmSetState(newSMState);
            triggerIn.DiscardTrigger();
        }
        else if (triggerInOut.IsTrigger()) {
            SMStateType requestedSMState = triggerInOut.GetDesiredState();
            FunctionGroupStateType newSMState = FunctionGroupStateType::Shutdown;
            if (requestedSMState == SMStateType::On) {
                newSMState = FunctionGroupStateType::On;
            } else if (requestedSMState == SMStateType::Off) {
                newSMState = FunctionGroupStateType::Off;
            }

            stateClient->SmSetState(newSMState);
            if (stateClient != nullptr) {
                internalState = stateClient->requestedSMState;
            }
            triggerInOut.SetNotifier(ara::sm::ErrorType::kSuccess, internalState);
            triggerInOut.DiscardTrigger();
        }

        if (stateClient != nullptr) {
            internalState = stateClient->requestedSMState;
        }
        if (executionClient != nullptr) {
            executionClient->ReportApplicationState(internalState);
        }
        triggerOut.SetNotifier(internalState);
    }

    void StateManagement::Kill() {
        killFlag = true;
    }

    StateManagement::StateManagement(exec::StateClient* sc, exec::ExecutionClient* ec) :
        myUpdateRequest{com::UpdateRequest()},
        myNetworkHandle{com::NetworkHandle()},
        triggerOut{com::TriggerOut()},
        triggerIn{com::TriggerIn()},
        triggerInOut{com::TriggerInOut()},
        stateClient{sc},
        executionClient{ec},
        killFlag{false} {}
}
