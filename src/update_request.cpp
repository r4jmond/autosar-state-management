#include "update_request.h"

namespace ara { namespace com {
    UpdateRequest::UpdateRequest() : ongoingUpdate{false}, resetRequest{false} {}

    void UpdateRequest::ResetMachine() {
        resetRequest = true;
    }

    void UpdateRequest::StartUpdateSession() {
        ongoingUpdate = true;
    }

    bool UpdateRequest::isOngoingUpdate() const {
        return ongoingUpdate;
    }

    void UpdateRequest::StopUpdateSession() {
        ongoingUpdate = false;
    }

    bool UpdateRequest::isResetRequest() const {
        return resetRequest;
    }
}}