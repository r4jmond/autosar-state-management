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
            if (stateClient != nullptr) {
                stateClient->SmSetState(triggerInOut.GetDesiredState());
            }
            triggerIn.DiscardTrigger();
        }
        else if (triggerInOut.IsTrigger()) {

            if (stateClient != nullptr) {
                stateClient->SmSetState(triggerInOut.GetDesiredState());
                internalState = stateClient->SmGetState();
            }
            triggerInOut.SetNotifier(ara::sm::ErrorType::kSuccess, internalState);
            triggerInOut.DiscardTrigger();
        }

        if (stateClient != nullptr) {
            internalState = stateClient->SmGetState();
        }
        triggerOut.SetNotifier(internalState);
    }

    void StateManagement::Kill() {
        killFlag = true;
    }

    StateManagement::StateManagement(exec::StateClient* sc) :
        myUpdateRequest{com::UpdateRequest()},
        myNetworkHandle{com::NetworkHandle()},
        triggerOut{com::TriggerOut()},
        triggerIn{com::TriggerIn()},
        triggerInOut{com::TriggerInOut()},
        internalState{FunctionGroupStateType::Off},
        stateClient{sc},
        killFlag{false} {}
}
