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

        void Initialize();

        void Work();

        void Exit();

        com::UpdateRequest myUpdateRequest;
        /** @brief Fills [SWS_SM_00020] */
        com::TriggerOut triggerOut;
        /** @brief Fills [SWS_SM_00021] */
        com::TriggerIn triggerIn;
        com::TriggerInOut triggerInOut;
    private:
        bool killFlag;
    };
}}

#endif //AUTOSAR_STATE_MANAGEMENT_STATE_MANAGEMENT_H
