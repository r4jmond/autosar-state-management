#ifndef AUTOSAR_STATE_MANAGEMENT_RECOVERY_ACTION_H
#define AUTOSAR_STATE_MANAGEMENT_RECOVERY_ACTION_H
/** @file recovery_action.h
  * @brief Interface used by Platform Health Manager (PHM)*/

namespace ara::phm {
        /** @brief Class RecoveryAction used by PHM to trigger recovery action in case any process behaves not within
                   the specified parameters.
          *         Fills [SWS_Platform_Health_Management]. */
        template<typename errorHandler>
        class RecoveryAction {
        private:
            bool errorOccurred;
            errorHandler handler;

        public:
            /** @brief UpdateRequest constructor. */
            RecoveryAction() : errorOccurred{false}, handler{} {}

            /**
             * @brief raiseError
             * @details Set errorOccurred flag to true and bind error to internal variable. Method used bu PHM.
             * @param[in] errorType - Pointer to the error handler specific to error that occurred.
             * @return None.
            */
            void raiseError(errorHandler* errorType){
                this->errorOccurred = true;
                this->handler = *errorType;
            }

        public:
            /**
              * @brief RecoveryActionHandler
              * @details Callback function used by State Manager to check if PHM reported any errors..
              * @param[in] errorType - Pointer to the error handler specific to error that occurred..
              * @return boolean : true if any error is reported and false if everything is OK.
             */
            bool recoveryActionHandler(errorHandler* errorRecovery){
                bool tempErrorOcurred;
                *errorRecovery = handler;
                tempErrorOcurred = errorOccurred;
                this->errorOccurred = false;
                return tempErrorOcurred;
            }
        };

} // ara::phm

#endif //AUTOSAR_STATE_MANAGEMENT_RECOVERY_ACTION_H