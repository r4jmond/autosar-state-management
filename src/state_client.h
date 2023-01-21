#ifndef AUTOSAR_STATE_MANAGEMENT_STATE_CLIENT_H
#define AUTOSAR_STATE_MANAGEMENT_STATE_CLIENT_H
/** @file state_client.h
 * @brief State Client EM interface. */

#include "sm_types.h"

namespace ara { namespace exec {
    /** @brief Class StateClient to be used for communication between SM and EM */
    class StateClient {
    public:
        /** @brief Variable to store the result of AUTOSAR Adaptive Platform initial transition to Startup state. */
        bool InitialMachineStateTransitionResult;
    public:
        /**
        * @brief ComSetState
        * @details Request a state transition for Com FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void ComSetState(sm::FunctionGroupStateType);
        /**
        * @brief DiagSetState
        * @details Request a state transition for Diag FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void DiagSetState(sm::FunctionGroupStateType);
        /**
        * @brief PhmSetState
        * @details Request a state transition for Phm FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void PhmSetState(sm::FunctionGroupStateType);
        /**
        * @brief ExecSetState
        * @details Request a state transition for Exec FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void ExecSetState(sm::FunctionGroupStateType);
    protected:
        /**
        * @brief GetInitialMachineStateTransitionResult
        * @details Retrieve the result of AUTOSAR Adaptive Platform initial transition to Startup state.
        */
        void GetInitialMachineStateTransitionResult();
    };
}}

#endif //AUTOSAR_STATE_MANAGEMENT_STATE_CLIENT_H
