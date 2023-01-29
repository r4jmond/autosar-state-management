#ifndef AUTOSAR_STATE_MANAGEMENT_STATE_CLIENT_H
#define AUTOSAR_STATE_MANAGEMENT_STATE_CLIENT_H
/** @file state_client.h
 * @brief State Client EM interface. */

#include "sm_types.h"

namespace ara::exec {

    /** @brief Simplified version of Execution Management error codes
     *  @details from the [SWS_EM_02281] */
    enum class ExecErrc {
        /** No error */
        kSuccess = 0,
        /** Error occured */
        kGeneralError = 1,
    };

    /** @brief Class StateClient to be used for communication between SM and EM */
    class StateClient {
    private:
        /** @brief Variable to store the result of AUTOSAR Adaptive Platform initial transition to Startup state. */
        bool initialMachineStateTransitionResult;

        /** @brief Variable to store requested SM state after calling SMSetState. */
        sm::FunctionGroupStateType requestedSMState;
    public:
        StateClient()
                : initialMachineStateTransitionResult(false),
                  requestedSMState(sm::FunctionGroupStateType::Off) {}

        /**
        * @brief GetInitialMachineStateTransitionResult
        * @details Retrieve the result of AUTOSAR Adaptive Platform initial transition to Startup state.
        */
        void GetInitialMachineStateTransitionResult();
        /**
        * @brief undefinedStateCallback
        * @details Gives an information whether desired state is valid.
        */
        void undefinedStateCallback();

        /**
        * @brief SmSetState
        * @details Requests a state transition for SM FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        * @return error code
        */
        ExecErrc SmSetState(sm::FunctionGroupStateType smState);
        /**
        * @brief Gets requested SM state.
        * @return Requested SM state.
        */
        sm::FunctionGroupStateType SmGetState();

        /**
        * @brief SetState
        * @details Request a state transition for given Function Group..
        * @param[in] fgName - name of the Function Group to be set.
        * @param[in] fgState - FunctionGroupState to be set
        * @return error code
        */
        ExecErrc SetState(std::string fgName, sm::FunctionGroupStateType fgState);
    };
}

#endif //AUTOSAR_STATE_MANAGEMENT_STATE_CLIENT_H
