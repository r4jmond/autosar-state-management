//
// Created by Filip Księżyc on 21.01.2023.
//

#include "recovery_action.h"

namespace ara {
    namespace phm {
        template<typename errorHandler>
        void RecoveryAction<errorHandler>::raiseError(errorHandler *errorType){
            this->errorOccurred = true;
            this->handler = *errorType;
        }

        template<typename errorHandler>
        bool RecoveryAction<errorHandler>::recoveryActionHandler(errorHandler *errorRecovery){
            *errorRecovery = handler;
            return this->errorOccurred;
        }

    } // ara
} // phm