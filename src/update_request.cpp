#include "update_request.h"

namespace ara::com {
    UpdateRequest::UpdateRequest() :
        requestMsg {false, RequestType::kResetMachine},
        updateStatus {sm::ErrorType::kSuccess}{}

    sm::ErrorType UpdateRequest::ResetMachine() {
        return SendRequest(RequestType::kResetMachine);
    }

    sm::ErrorType UpdateRequest::StopUpdateSession() {
        return SendRequest(RequestType::kStopUpdateSession);
    }

    sm::ErrorType UpdateRequest::RequestUpdateSession() {
        return SendRequest(RequestType::kRequestUpdateSession);
    }
    
    sm::ErrorType UpdateRequest::PrepareUpdate(sm::FunctionGroupListType const &functionGroupList) {
        UpdateRequest::functionGroupListToSM = functionGroupList;
        return SendRequest(RequestType::kPrepareUpdate);
    }

    sm::ErrorType UpdateRequest::VerifyUpdate(sm::FunctionGroupListType const &functionGroupList) {
        UpdateRequest::functionGroupListToSM = functionGroupList;
        return SendRequest(RequestType::kVerifyUpdate);
    }

    sm::ErrorType UpdateRequest::PrepareRollback(sm::FunctionGroupListType const &functionGroupList) {
        UpdateRequest::functionGroupListToSM = functionGroupList;
        return SendRequest(RequestType::kPrepareRollback);
    }

    void UpdateRequest::SendResponse(sm::ErrorType newUpdateStatus) {
        UpdateRequest::updateStatus = newUpdateStatus;
        requestMsg.status = false;
    }

    UpdateRequest::RequestMsg &UpdateRequest::GetRequestMsg() {
        return UpdateRequest::requestMsg;
    }

    sm::ErrorType UpdateRequest::SendRequest(UpdateRequest::RequestType requestType) {
        /* Set request flag to true */
        UpdateRequest::requestMsg.type = requestType;
        UpdateRequest::requestMsg.status = true;
        /* Wait for SM to clear smRequest flag */
        while(UpdateRequest::requestMsg.status) {}
        /* return smResponse set by SM */
        return updateStatus;
    }
    const sm::FunctionGroupListType &UpdateRequest::GetFunctionGroupList() const {
        return functionGroupListToSM;
    }

    sm::ErrorType UpdateRequest::GetUpdateStatus() const {
        return updateStatus;
    }
}
