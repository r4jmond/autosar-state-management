#include "ecu_reset_request.h"

namespace ara::dia {
    EcuResetRequest::EcuResetRequest() :
            requestMsg {false, RequestType::kRequestReset} {}

    void EcuResetRequest::EnableRapidShutdown() {
        return SendRequest(RequestType::kEnableRapidShutdown);
    }

    void EcuResetRequest::DisableRapidShutdown() {
        return SendRequest(RequestType::kDisableRapidShutdown);
    }

    void EcuResetRequest::ExecuteReset() {
        return SendRequest(RequestType::kExecuteReset);
    }

    void EcuResetRequest::RequestReset() {
        return SendRequest(RequestType::kRequestReset);
    }

    void EcuResetRequest::KeyOffOnReset() {
        return SendRequest(RequestType::kRequestReset);
    }

    void EcuResetRequest::DiscardRequest() {
        /* Set request flag to false */
        EcuResetRequest::requestMsg.status = false;
    }

    EcuResetRequest::RequestMsg &EcuResetRequest::GetRequestMsg() {
        return EcuResetRequest::requestMsg;
    }

    void EcuResetRequest::SendRequest(EcuResetRequest::RequestType requestType) {
        EcuResetRequest::requestMsg.type = requestType;
        /* Set request flag to true */
        EcuResetRequest::requestMsg.status = true;
    }
}
