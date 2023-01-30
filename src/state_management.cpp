#include "state_management.h"
#include <iostream>
#include "contains.h"

namespace ara::sm {

    void StateManagement::Work() {
        std::cout << "Starting work" << std::endl;
        /** @brief Start-up Sequence - Figure 7.1 SWS_StateManagement */
        if (stateClient != nullptr) {
            if (stateClient->GetInitialMachineStateTransitionResult() == ErrorType::kSuccess) {
                stateClient->SmSetState(FunctionGroupStateType::On);
            }
            /* Restart machine if Initial MachineState Transition not successful */
            else stateClient->MachineSetState(MachineStateType::Restart);
        }

        while (!killFlag) {
            if (internalState == FunctionGroupStateType::Off) {
                Off_Actions();
            }
            else if (internalState == FunctionGroupStateType::On) {
                On_Actions();
            }
            else if (internalState == FunctionGroupStateType::Update) {
                //do stuff
            }
            UpdateSMState();
        }
        std::cout << "Finished work" << std::endl;
    }

    void StateManagement::On_Actions() {
        UpdateRequestHandler();
        TriggerInHandler();
        TriggerInOutHandler();
    }

    void StateManagement::Off_Actions() {
        UpdateRequestHandler();
        TriggerInHandler();
        TriggerInOutHandler();
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
        if (executionClient != nullptr) {
            executionClient->ReportApplicationState(internalState);
        }
        triggerOut.SetNotifier(internalState);
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

    void StateManagement::ErrorHandler(){
        if(recoveryAction.RecoveryActionHandler(&errorMessage)){
            if(errorOccurred){
                //todo MachineSetState(restart);
            }
            std::cout << errorMessage << std::endl;
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

    void StateManagement::ConnectClientToServer(std::string clientID, com::PowerMode* client){
        communicationGroupServer.AddClientToGroup(clientID, client);
    }

    void StateManagement::SendPowerModeStatus(std::string mode){
        communicationGroupServer.Broadcast(mode);
    }

    StateManagement::StateManagement(exec::StateClient* sc, exec::ExecutionClient* ec) :
        myUpdateRequest{com::UpdateRequest()},
        myNetworkHandle{com::NetworkHandle()},
        triggerOut{com::TriggerOut()},
        triggerIn{com::TriggerIn()},
        triggerInOut{com::TriggerInOut()},
        internalState{FunctionGroupStateType::Off},
        stateClient{sc},
        executionClient{ec},
        killFlag{false},
        errorOccurred{false} {}
}
