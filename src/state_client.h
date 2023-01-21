#ifndef AUTOSAR_STATE_MANAGEMENT_STATE_CLIENT_H
#define AUTOSAR_STATE_MANAGEMENT_STATE_CLIENT_H

#include "sm_types.h"

namespace ara { namespace exec {
    class StateClient {
    private:
        bool InitialMachineStateTransitionResult;
    public:
        StateClient();
        void ComSetState(sm::FunctionGroupStateType);
        void DiagSetState(sm::FunctionGroupStateType);
        void PhmSetState(sm::FunctionGroupStateType);
        void ExecSetState(sm::FunctionGroupStateType);

    protected:
        void GetInitialMachineStateTransitionResult();
    };
}}

#endif //AUTOSAR_STATE_MANAGEMENT_STATE_CLIENT_H
