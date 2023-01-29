//
// Created by Filip Księżyc on 21.01.2023.
//
#include <iostream>
#include "recovery_action.h"




int main(){
    int pnt = 0;

    std::cout << "Hello, world!" << std::endl;

    ara::phm::RecoveryAction<int> dupa;

    std::cout << dupa.recoveryActionHandler(&pnt) << std::endl;
    pnt = 5;
    dupa.raiseError(&pnt);
    pnt = 0;
    std::cout << pnt << std::endl;
    std::cout << dupa.recoveryActionHandler(&pnt) << std::endl;
    std::cout << pnt << std::endl;

    return 0;
}