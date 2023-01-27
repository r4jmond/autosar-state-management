#include "state_management.h"
#include <iostream>

namespace ara { namespace sm {

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
    }

    void StateManagement::Kill() {
        killFlag = true;
    }

    StateManagement::StateManagement() :
        myUpdateRequest{com::UpdateRequest()},
        myNetworkHandle{com::NetworkHandle()},
        triggerOut{com::TriggerOut()},
        triggerIn{com::TriggerIn()},
        triggerInOut{com::TriggerInOut()},
        killFlag{false} {}
}}
