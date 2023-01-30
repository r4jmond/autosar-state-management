#ifndef AUTOSAR_STATE_MANAGEMENT_STATE_MANAGEMENT_H
#define AUTOSAR_STATE_MANAGEMENT_STATE_MANAGEMENT_H
/** @file state_management.h
 * @brief State Management main header file. */

#include "sm_types.h"
#include "update_request.h"
#include "trigger_in.h"
#include "trigger_in_out.h"
#include "trigger_out.h"
#include "network_handle.h"
#include "state_client.h"
#include "ecu_reset_request.h"
#include "execution_client.h"
#include "communication_group_server.h"
#include "recovery_action.h"
#include "diagnostic_reset.h"

namespace ara::sm {
    /** @brief Class StateManagement to be used by Update and Configuration Management.
     *         Fills [SWS_SM_XXXXX]. */
    class StateManagement {
    public:
        explicit StateManagement(exec::StateClient* sc, exec::ExecutionClient* ec);
        /** @brief Start function of the SM */
        void Work();
        /** @brief Function killing SM operation */
        void Kill();
        com::UpdateRequest myUpdateRequest;
        com::NetworkHandle myNetworkHandle;
        /** @brief Fills [SWS_SM_00020] */
        com::TriggerOut triggerOut;
        /** @brief Fills [SWS_SM_00021] */
        com::TriggerIn triggerIn;
        com::TriggerInOut triggerInOut;
        FunctionGroupStateType internalState;
        exec::StateClient* stateClient;
        dia::EcuResetRequest ecuResetRequest;
        bool GetShutdownFlag() const;
        phm::RecoveryAction<std::string> recoveryAction;
        com::CommunicationGroupServer<com::PowerMode*> communicationGroupServer;
    private:
        /** @brief SM kill flag */
        bool killFlag;
        /** @brief Rapid shutdown flag */
        bool rapidShutdownFlag;
        exec::ExecutionClient* executionClient;

        /** @brief SM error occurred flag */
        bool errorOccurred;
        /** @brief String to store error message from phm */
        std::string errorMessage;
        /** @brief Function handling SM 'On' State operations */
        void On_Actions();

        /** @brief Function handling SM 'Off' State operations */
        void Off_Actions();

        /** @brief Function handling TriggerIn */
        void TriggerInHandler();

        /** @brief Function handling TriggerInOut */
        void TriggerInOutHandler();

        /** @brief Function used to add Client Processes to Server */
        void ConnectClientToServer(std::string clientID, com::PowerMode* client);
        /** @brief Function to check if PHM report errors and providing recovery action for them */
        void ErrorHandler();
        /** @brief Function sending power mode change to all processes */
        void SendPowerModeStatus(std::string mode);

        /** @brief Function Updating SM State on EM request
        *   @details After updating it reports it's internal state to EM and TriggerOut. */
        void UpdateSMState();

        /** @brief Checks for Update Requests and handles them
         *  @details Should work in 'On' SM state.
         *  Handles request: RequestUpdateSession */
        void UpdateRequestHandlerOn();

        /** @brief Checks for Update Requests and handles them
         *  @details Should work in 'Off' SM state.
         *  Rejects all requests as in Off state updates are not allowed. */
        void UpdateRequestHandlerOff();

        /** @brief Checks for Update Requests and handles them
         *  @details Should work in 'Update' SM state.
         *  Handles all requests. */
        void UpdateRequestHandlerUpdate();

        /** @brief Checks for ECU Reset Requests and handles them */
        void EcuResetRequestHandler();

        /** @brief Checks if given FunctionGroupList is valid
         * @param[in] fgList - FunctionGroupList to be checked.
         * @return true if list is valid, false otherwise */
        bool CheckFunctionGroupList(FunctionGroupListType const &fgList);

        /** @brief Sets all function groups from fgList to given state.
         *  @param[in] fgList - list of function groups to be set.
         *  @param[in] fgState - new function group state.
         *  @return error code
         */
        [[nodiscard]] ErrorType SetAllFunctionGroupsState(const FunctionGroupListType &fgList,
                                                             FunctionGroupStateType fgState) const;

        /** @brief List of used FunctionGroups. Fills [SWS_SM_00001].
        *  @details Normally it would be read from manifest, but we use static configuration here */
        const FunctionGroupListType functionGroupList { FunctionGroupNameType::exec,
                                                        FunctionGroupNameType::phm,
                                                        FunctionGroupNameType::diag,
                                                        FunctionGroupNameType::ucm,
                                                        FunctionGroupNameType::nm };
    };
}

#endif //AUTOSAR_STATE_MANAGEMENT_STATE_MANAGEMENT_H
