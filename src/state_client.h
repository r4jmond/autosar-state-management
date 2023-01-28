#ifndef AUTOSAR_STATE_MANAGEMENT_STATE_CLIENT_H
#define AUTOSAR_STATE_MANAGEMENT_STATE_CLIENT_H
/** @file state_client.h
 * @brief State Client EM interface. */

#include "sm_types.h"

namespace ara::exec {
    /** @brief Class StateClient to be used for communication between SM and EM */
    class StateClient {
    public:
        /** @brief Variable to store the result of AUTOSAR Adaptive Platform initial transition to Startup state. */
        bool initialMachineStateTransitionResult;

        /** @brief Variable to store requested SM state after calling SMSetState. */
        ara::sm::SMStateType requestedSMState;
    public:
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

        // methods for SM

        /**
        * @brief CoreSetState
        * @details Request a state transition for Core FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void CoreSetState(sm::FunctionGroupStateType);
        /**
        * @brief ComSetState
        * @details Request a state transition for Com FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void ComSetState(sm::FunctionGroupStateType);
        /**
        * @brief CryptoSetState
        * @details Request a state transition for Crypto FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void CryptoSetState(sm::FunctionGroupStateType);
        /**
        * @brief DiagSetState
        * @details Request a state transition for Diag FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void DiagSetState(sm::FunctionGroupStateType);
        /**
        * @brief ExecSetState
        * @details Request a state transition for Exec FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void ExecSetState(sm::FunctionGroupStateType);
        /**
        * @brief FwSetState
        * @details Request a state transition for Fw FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void FwSetState(sm::FunctionGroupStateType);
        /**
        * @brief IamSetState
        * @details Request a state transition for Iam FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void IamSetState(sm::FunctionGroupStateType);
        /**
        * @brief IdsmSetState
        * @details Request a state transition for Idsm FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void IdsmSetState(sm::FunctionGroupStateType);
        /**
        * @brief LogSetState
        * @details Request a state transition for Log FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void LogSetState(sm::FunctionGroupStateType);
        /**
        * @brief NmSetState
        * @details Request a state transition for Nm FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void NmSetState(sm::FunctionGroupStateType);
        /**
        * @brief NaSetState
        * @details Request a state transition for N/a FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void NaSetState(sm::FunctionGroupStateType);
        /**
        * @brief PerSetState
        * @details Request a state transition for Per FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void PerSetState(sm::FunctionGroupStateType);
        /**
        * @brief PhmSetState
        * @details Request a state transition for Phm FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void PhmSetState(sm::FunctionGroupStateType);
        /**
        * @brief SmSetState
        * @details Request a state transition for Sm FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void SmSetState(sm::FunctionGroupStateType);
        /**
        * @brief TsyncSetState
        * @details Request a state transition for Tsync FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void TsyncSetState(sm::FunctionGroupStateType);
        /**
        * @brief UcmSetState
        * @details Request a state transition for Ucm FunctionGroup.
        * @param[in] FunctionGroupStateType - FunctionGroupState to be set
        */
        void UcmSetState(sm::FunctionGroupStateType);
    };
}

#endif //AUTOSAR_STATE_MANAGEMENT_STATE_CLIENT_H
