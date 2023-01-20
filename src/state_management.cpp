#include "state_management.h"
#include <iostream>

namespace ara { namespace sm {

    void StateManagement::Initialize() {
        std::cout << "Initialization complete" << std::endl;
    }

    void StateManagement::Work() {
        std::cout << "Starting work" << std::endl;
        while (!killFlag) {

            if (myUpdateRequest.IsResetRequest()) {
                // reset
            } else {
                //don't reset??
            }
        }
    }

    void StateManagement::Exit() {
        std::cout << "Exit completed" << std::endl;
    }

    StateManagement::StateManagement() :
            myUpdateRequest{com::UpdateRequest()}, killFlag{false} {}
}}
