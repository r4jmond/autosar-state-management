#include "state_management.h"
#include <iostream>

namespace ara { namespace sm {

    void StateManagement::Work() {
        std::cout << "Starting work" << std::endl;
        while (!killFlag) {
            Worker();
        }
    }

    void StateManagement::Worker() {
        if (myUpdateRequest.IsResetRequest()) {
            myUpdateRequest.SetResetRequest(false);
            myUpdateRequest.SetResetAccepted(true);
        } else {
            //don't reset??
        }
    }

    void StateManagement::Kill() {
        killFlag = true;
    }

    StateManagement::StateManagement() :
            myUpdateRequest{com::UpdateRequest()}, killFlag{false} {}


}}
