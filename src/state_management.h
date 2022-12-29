#ifndef AUTOSAR_STATE_MANAGEMENT_STATE_MANAGEMENT_H
#define AUTOSAR_STATE_MANAGEMENT_STATE_MANAGEMENT_H
#include <string>
#include "update_request.h"

/** @brief Fills [SWS_SM_91012] */
typedef enum Resp_Type
{
    kDone,        /* requested mode sucessfully reached.                             */
    kFailed,      /* requested mode not reached.                                     */
    kBusy,        /* can't process requested mode e.g. important things are ongoing. */
    kNotSupported /* requested mode not supported.                                   */
} Resp_T;

typedef enum Error_Type
{
    kSuccess                          = 0,
    kRejected                         = 5, /* Requested operation was rejected due to State Management
                                              machines internal state.            */
    kVerifyFailed                     = 6, /* Verification step of update failed. */
    kPrepareFailed                    = 7, /* Preparation step of update failed.  */
    kRollbackFailed                   = 8, /* Rollback step of update failed.     */
    kNotAllowedMultipleUpdateSessions = 9  /* Request for new session was rejected as only single active
                                              (update) session is allowed.        */
} Error_T;

typedef enum SM_State_Type
{
    Start_Engine,
    Drive,
    Shutdown
} SM_State_T;

class StateManagement
{
public:
    StateManagement();
    void Initialize();
    void Work();
    void Exit();
    UpdateRequest myUpdateRequest;
private:
    bool killFlag;
    bool ongoingUpdate;
};

#endif //AUTOSAR_STATE_MANAGEMENT_STATE_MANAGEMENT_H
