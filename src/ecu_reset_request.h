#ifndef AUTOSAR_STATE_MANAGEMENT_ECU_RESET_REQUEST_H
#define AUTOSAR_STATE_MANAGEMENT_ECU_RESET_REQUEST_H

/** @file ecu_reset_request.h
 * @brief EcuResetRequest diagnostic interface. */

#include "sm_types.h"

namespace ara::dia {
    /** @brief Class EcuResetRequest to be used for resetting.
     *         Fills [ISO 14229-1]. */
    class EcuResetRequest {
    public:

        EcuResetRequest();
        /** @brief Enable Rapid Shutdown functionality .
         * @details Fills [SWS_SM_00106].
         */
        void EnableRapidShutdown();
        /** @brief Disable Rapid Shutdown functionality .
        * @details Fills [SWS_SM_00107].
        */
        void DisableRapidShutdown();
        /** @brief Perform hard reset */
        void ExecuteReset();
        /** @brief Perform hard reset with propagating information to processes */
        void RequestReset();
        /** @brief Perform key off-on reset */
        void KeyOffOnReset();

        /** @brief Type of request sent to SM */
        enum class RequestType {
            /** Enable Rapid Shutdown */
            kEnableRapidShutdown,
            /** Disable Rapid Shutdown */
            kDisableRapidShutdown,
            /** Perform hard reset*/
            kExecuteReset,
            /** Perform hard reset with propagating information to processes */
            kRequestReset,
            /** Perform key off-on reset */
            kKeyOffOnReset,
        };

        /** @brief RequestMsg sent to SM */
        struct RequestMsg {
            /** status of request (true - active) */
            bool status;
            /** type of request */
            RequestType type;
        };

    private:
        RequestMsg requestMsg;
        /** @brief Sends request to SM.
         *  @param [in] requestType - type of request sent to SM
         */
        void SendRequest(RequestType requestType);
    public:
        /** @brief smRequest getter used by SM
         * @return request sent to the SM */
        RequestMsg &GetRequestMsg();
        /** @brief Set request status to inactive */
        void DiscardRequest();
    };
}


#endif //AUTOSAR_STATE_MANAGEMENT_ECU_RESET_REQUEST_H
