#ifndef AUTOSAR_STATE_MANAGEMENT_STATE_MANAGEMENT_H
#define AUTOSAR_STATE_MANAGEMENT_STATE_MANAGEMENT_H
#include <string>
#include "update_request.h"
#include "trigger_in.h"
#include "trigger_in_out.h"
#include "trigger_out.h"
#include "network_handle.h"

namespace ara { namespace sm {

    /** @brief Fills [SWS_SM_91012] */
    typedef enum RespType {
        kDone,        /* requested mode sucessfully reached.                             */
        kFailed,      /* requested mode not reached.                                     */
        kBusy,        /* can't process requested mode e.g. important things are ongoing. */
        kNotSupported /* requested mode not supported.                                   */
    } RespT;

    /** @brief Fills [SWS_SM_91010] */
    typedef enum ErrorType {
        kSuccess = 0,
        kRejected = 5, /* Requested operation was rejected due to State Management
                                                  machines internal state.            */
        kVerifyFailed = 6, /* Verification step of update failed. */
        kPrepareFailed = 7, /* Preparation step of update failed.  */
        kRollbackFailed = 8, /* Rollback step of update failed.     */
        kNotAllowedMultipleUpdateSessions = 9  /* Request for new session was rejected as only single active
                                                  (update) session is allowed.        */
    } ErrorT;

    /** @brief Fills [RS_SM_00005] */
    typedef enum SMStateType {
        Start_Engine,
        Drive,
        Shutdown
    } SMStateT;

    class StateManagement {
    public:
        StateManagement();

        void Initialize();

        void Work();

        void Exit();

        com::UpdateRequest myUpdateRequest;
        com::NetworkHandle myNetworkHandle;
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
