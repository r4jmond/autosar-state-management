#include "update_request.h"

namespace ara { namespace com {
    UpdateRequest::UpdateRequest() : resetRequest{false}, resetAccepted{false},
                                     updateRequest{false}, updateSession {false},
                                     updateAccepted {false} {}

    sm::ErrorType UpdateRequest::ResetMachine() {
        /* set resetRequest */
        resetRequest = true;
        /* wait for State management to clear resetRequest */
        while (resetRequest) {}
        /* SM sets resetAccepted after reading resetRequest */
        return resetAccepted ? sm::ErrorType::kSuccess : sm::ErrorType::kRejected;
    }
    sm::ErrorType UpdateRequest::StopUpdateSession() {
        if (updateSession) {
            updateSession = false;
            return sm::ErrorType::kSuccess;
        }
        else {
            return sm::ErrorType::kRejected;
        }
    }
    sm::ErrorType UpdateRequest::RequestUpdateSession() {
        if (updateSession) {
            return sm::ErrorType::kNotAllowedMultipleUpdateSessions;
        }
        else {
            updateRequest = true;
            while (updateRequest) {}
            return updateAccepted ? sm::ErrorType::kSuccess : sm::ErrorType::kRejected;
        }
    }
    sm::ErrorType UpdateRequest::PrepareUpdate(sm::FunctionGroupListType functionGroupList) {
        if (!updateSession) {
            return sm::ErrorType::kRejected;
        }
        else {
            UpdateRequest::functionGroupList = functionGroupList;
            updateRequest = true;
            while (updateRequest) {}
            return errorCode;
        }
    }


    bool UpdateRequest::IsResetRequest() const {
        return resetRequest;
    }
    void UpdateRequest::SetResetAccepted(bool isResetAccepted) {
        UpdateRequest::resetAccepted = isResetAccepted;
    }


    bool UpdateRequest::IsUpdateRequest() const {
        return updateRequest;
    }
    void UpdateRequest::SetUpdateRequest(bool newUpdateRequest) {
        UpdateRequest::updateRequest = newUpdateRequest;
    }
    bool UpdateRequest::IsUpdateSession() const {
        return updateSession;
    }
    void UpdateRequest::SetUpdateSession(bool newUpdateSession) {
        UpdateRequest::updateSession = newUpdateSession;
    }
    void UpdateRequest::SetUpdateAccepted(bool isUpdateAccepted) {
        UpdateRequest::updateAccepted = isUpdateAccepted;
    }

    const sm::FunctionGroupListType &UpdateRequest::GetFunctionGroupList() const {
        return functionGroupList;
    }

//    void UpdateRequest::SetErrorCode(sm::ErrorType errorCode) {
//        UpdateRequest::errorCode = errorCode;
//    }


}}