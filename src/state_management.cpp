
#include "state_management.h"
#include <iostream>

void StateManagement::Initialize()
{
    std::cout << "Initialization complete" << std::endl;
}

void StateManagement::Work()
{
    std::cout << "Starting work" << std::endl;
    while (!killFlag)
    {
        if (ongoingUpdate) {
            std::cout << "gościu update jest nie rób że " << std::endl;
        }
        ongoingUpdate = myUpdateRequest.isOngoingUpdate();

        if (myUpdateRequest.isResetRequest()) {
            // zrób reset gościu
        } else {
            //eeee nie rób reset??
        }

    }
}

void StateManagement::Exit()
{
    std::cout << "Exit completed" << std::endl;
}

StateManagement::StateManagement() :
                                 myUpdateRequest{UpdateRequest()}, killFlag{false},
                                 ongoingUpdate{false} {}
