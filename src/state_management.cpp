#include "state_management.h"
#include <iostream>
#include "contains.h"

namespace ara::sm {

    void StateManagement::Work() {
        std::cout << "Starting work" << std::endl;
        if (stateClient != nullptr) {
            if (stateClient->GetInitialMachineStateTransitionResult() == ErrorType::kSuccess) {
                stateClient->SmSetState(FunctionGroupStateType::On);
            }
            else stateClient->MachineSetState(MachineStateType::Restart);
        }
        while (!killFlag) {
            if (internalState == FunctionGroupStateType::Off) {
                On_Actions();
            }
            else if (internalState == FunctionGroupStateType::On) {
                Off_Actions();
            }
            triggerOut.SetNotifier(internalState);
        }
        std::cout << "Finished work" << std::endl;
    }

    void StateManagement::On_Actions() {
        EcuResetRequestHandler();
        UpdateRequestHandler();
        TriggerInHandler();
        TriggerInOutHandler();
        UpdateSMState();
    }

    void StateManagement::Off_Actions() {
        EcuResetRequestHandler();
        UpdateRequestHandler();
        TriggerInHandler();
        TriggerInOutHandler();
        UpdateSMState();
    }

    void StateManagement::TriggerInHandler() {
        if (triggerIn.IsTrigger()) {
            if (stateClient != nullptr) {
                stateClient->SmSetState(triggerInOut.GetDesiredState());
            }
            triggerIn.DiscardTrigger();
        }
    }

    void StateManagement::TriggerInOutHandler() {
        if (triggerInOut.IsTrigger()) {

            if (stateClient != nullptr) {
                stateClient->SmSetState(triggerInOut.GetDesiredState());
                internalState = stateClient->SmGetState();
            }
            triggerInOut.SetNotifier(ara::sm::ErrorType::kSuccess, internalState);
            triggerInOut.DiscardTrigger();
        }
    }

    void StateManagement::UpdateSMState() {
        if (stateClient != nullptr) {
            internalState = stateClient->SmGetState();
        }
    }

    void StateManagement::UpdateRequestHandler() {
        com::UpdateRequest::RequestMsg requestMsg =  myUpdateRequest.GetRequestMsg();
        if (requestMsg.status) {
            ErrorType newUpdateStatus;
            switch (requestMsg.type) {
                case com::UpdateRequest::RequestType::kRequestUpdateSession:
                    if (myUpdateRequest.IsUpdateSession()) {
                        newUpdateStatus = ErrorType::kNotAllowedMultipleUpdateSessions;
                    }
                    else {
                        myUpdateRequest.SetUpdateSession(true);
                        newUpdateStatus = ErrorType::kSuccess;
                    }
                    break;
                case com::UpdateRequest::RequestType::kStopUpdateSession:
                    if (myUpdateRequest.IsUpdateSession()) {
                        myUpdateRequest.SetUpdateSession(false);
                        newUpdateStatus = ErrorType::kSuccess;
                    }
                    else {
                        newUpdateStatus = ErrorType::kRejected;
                    }
                    break;
                case com::UpdateRequest::RequestType::kResetMachine:
                    if (myUpdateRequest.IsUpdateSession()) {
                        // todo persist all information within the machine
                        // todo reset machine
                        newUpdateStatus = ErrorType::kSuccess;
                    }
                    else {
                        newUpdateStatus = ErrorType::kRejected;
                    }
                    break;
                case com::UpdateRequest::RequestType::kPrepareUpdate:
                    if (myUpdateRequest.IsUpdateSession()) {
                        if (CheckFunctionGroupList(myUpdateRequest.GetFunctionGroupList())) {
                            //todo prepare update
                            newUpdateStatus = ErrorType::kSuccess;
                        }
                        else {
                            newUpdateStatus = ErrorType::kFailed;
                        }
                    }
                    else {
                        newUpdateStatus = ErrorType::kRejected;
                    }
                    break;
                case com::UpdateRequest::RequestType::kVerifyUpdate:
                    if ((myUpdateRequest.IsUpdateSession()) &&
                        (myUpdateRequest.GetUpdateStatus() == ErrorType::kSuccess)) {
                        if (CheckFunctionGroupList(myUpdateRequest.GetFunctionGroupList())) {
                            //todo verify update
                            newUpdateStatus = ErrorType::kSuccess;
                        } else {
                            newUpdateStatus = ErrorType::kFailed;
                        }
                    }
                    else {
                        newUpdateStatus = ErrorType::kRejected;
                    }
                    break;
                case com::UpdateRequest::RequestType::kPrepareRollback:
                    if ((myUpdateRequest.IsUpdateSession()) &&
                        (myUpdateRequest.GetUpdateStatus() == ErrorType::kFailed)) {
                        if (CheckFunctionGroupList(myUpdateRequest.GetFunctionGroupList())) {
                            //todo prepare rollback
                            newUpdateStatus = ErrorType::kSuccess;
                        } else {
                            newUpdateStatus = ErrorType::kFailed;
                        }
                    }
                    else {
                        newUpdateStatus = ErrorType::kRejected;
                    }
            }

            myUpdateRequest.SendResponse(newUpdateStatus);
        }
    }

    void StateManagement::EcuResetRequestHandler() {
        if (ecuResetRequest.GetRequestMsg().status) {
            switch (ecuResetRequest.GetRequestMsg().type) {
                case dia::EcuResetRequest::RequestType::kEnableRapidShutdown:
                    rapidShutdownFlag = true;
                    break;
                case dia::EcuResetRequest::RequestType::kDisableRapidShutdown:
                    rapidShutdownFlag = false;
                    break;
                case dia::EcuResetRequest::RequestType::kExecuteReset:
                    stateClient->MachineSetState(MachineStateType::Restart);
                    break;
                case dia::EcuResetRequest::RequestType::kRequestReset:
                    // todo notify all processes about restart
                    if (!rapidShutdownFlag) {
                        //todo wait for response from function groups
                    }
                    stateClient->MachineSetState(MachineStateType::Restart);
                    break;
                case dia::EcuResetRequest::RequestType::kKeyOffOnReset:
                    // todo set al function groups to off and then to on
                    break;
                default:
                    break;
            }
            ecuResetRequest.DiscardRequest();
        }
    }

    bool StateManagement::CheckFunctionGroupList(FunctionGroupListType const &fgList) {

        std::vector<std::string> functionGroupListVec = std::ref(functionGroupList);
        return std::all_of(fgList.begin(), fgList.end(),
                           [&](const std::string &functionGroup)
                            { return VecContainsElement(functionGroupListVec, functionGroup); } );
    }

    void StateManagement::Kill() {
        killFlag = true;
    }

    bool StateManagement::GetShutdownFlag() const {
        return rapidShutdownFlag;
    }

    StateManagement::StateManagement(exec::StateClient* sc) :
        myUpdateRequest{com::UpdateRequest()},
        myNetworkHandle{com::NetworkHandle()},
        triggerOut{com::TriggerOut()},
        triggerIn{com::TriggerIn()},
        triggerInOut{com::TriggerInOut()},
        internalState{FunctionGroupStateType::Off},
        stateClient{sc},
        ecuResetRequest{dia::EcuResetRequest()},
        killFlag{false} {}
}
