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
#include "execution_client.h"

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
        exec::ExecutionClient* executionClient;
    private:
        /** @brief SM kill flag */
        bool killFlag;
        /** @brief Function handling SM 'On' State operations */
        void On_Actions();
        /** @brief Function handling SM 'Off' State operations */
        void Off_Actions();
        /** @brief Function handling TriggerIn */
        void TriggerInHandler();
        /** @brief Function handling TriggerInOut */
        void TriggerInOutHandler();
        /** @brief Function Updating SM State on EM request
        *   @details After updating it reports it's internal state to EM and TriggerOut.
        */
        void UpdateSMState();

        /** @brief Checks for Update Requests and handles them */
        void UpdateRequestHandler();

        /** @brief Checks if given FunctionGroupList is valid
         * @param fgList - FunctionGroupList to be checked.
         * @return true if list is valid, false otherwise */
        bool CheckFunctionGroupList(FunctionGroupListType const &fgList);

        /** @brief List of used FunctionGroups. Fills [SWS_SM_00001].
        *  @details Normally it would be read from manifest, but we use static configuration here */
        const FunctionGroupListType functionGroupList { FunctionGroupNameType::sm,
                                                        FunctionGroupNameType::exec,
                                                        FunctionGroupNameType::phm,
                                                        FunctionGroupNameType::diag,
                                                        FunctionGroupNameType::ucm,
                                                        FunctionGroupNameType::nm };
    };
}

#endif //AUTOSAR_STATE_MANAGEMENT_STATE_MANAGEMENT_H
