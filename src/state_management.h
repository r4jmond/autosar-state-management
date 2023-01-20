#ifndef AUTOSAR_STATE_MANAGEMENT_STATE_MANAGEMENT_H
#define AUTOSAR_STATE_MANAGEMENT_STATE_MANAGEMENT_H
/** @file state_management.h
 * @brief State Management main header file. */

#include "sm_types.h"
#include "update_request.h"
#include "trigger_in.h"
#include "trigger_in_out.h"
#include "trigger_out.h"

namespace ara { namespace sm {
    /** @brief Class StateManagement to be used by Update and Configuration Management.
     *         Fills [SWS_SM_XXXXX]. */
    class StateManagement {
    public:
        StateManagement();
        void Work();
        void Kill();
        com::UpdateRequest myUpdateRequest;
        /** @brief Fills [SWS_SM_00020] */
        com::TriggerOut triggerOut;
        /** @brief Fills [SWS_SM_00021] */
        com::TriggerIn triggerIn;
        com::TriggerInOut triggerInOut;
    private:
        bool killFlag;
        void Worker();
        /** @brief List of used FunctionGroups. Fills [SWS_SM_00001].
        *  @details Normally it would be read from manifest, but we use static configuration here */
        const FunctionGroupListType functionGroupList { FunctionGroupNameType::sm,
                                                        FunctionGroupNameType::exec,
                                                        FunctionGroupNameType::phm,
                                                        FunctionGroupNameType::diag,
                                                        FunctionGroupNameType::ucm,
                                                        FunctionGroupNameType::nm };
    };
}}

#endif //AUTOSAR_STATE_MANAGEMENT_STATE_MANAGEMENT_H
