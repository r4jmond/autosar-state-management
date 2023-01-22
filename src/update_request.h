#ifndef AUTOSAR_STATE_MANAGEMENT_UPDATE_REQUEST_H
#define AUTOSAR_STATE_MANAGEMENT_UPDATE_REQUEST_H
/** @file update_request.h
 * @brief Update Request SM interface to be used by UCM. */

#include "sm_types.h"

namespace ara::com {

    /** @brief Class UpdateRequest to be used by Update and Configuration Management.
     *         Fills [SWS_SM_91016]. */
    class UpdateRequest {
    public:
        /** @brief UpdateRequest constructor. */
        UpdateRequest();
        /**
        * @brief ResetMachine
        * @details Requests a reset of the machine.
        *          Before the reset is performed all information within the machine shall be persisted.
        *          Request will be rejected when RequestUpdateSession was not called successfully before.
        * @return error code
        */
        sm::ErrorType ResetMachine();
        /**
        * @brief StopUpdateSession
        * @details Has to be called by Update And Configuration Management once the update is finished to let State
                   Management know that the update is done and the Machine is in a stable state.
                   Request will be rejected when RequestUpdateSession was not called successfully before.
        * @return error code
        */
        sm::ErrorType StopUpdateSession();
        /**
         * @brief RequestUpdateSession
         * @details Has to be called by Update And Configuration Management once it has to start interaction with
         *          State Management.
         *          State Management might decline this request when machine is not in a state to be updated.
         * @return error code
         */
        sm::ErrorType RequestUpdateSession();
        /**
         * @brief PrepareUpdate
         * @details Has to be called by Update And Configuration Management after State Management allowed to update.
                    State Management will decline this request when RequestUpdateSession was not called before
                    successfully.
         * @param [in] updateFunctionGroupList - The list of FunctionGroups to be prepared to be updated.
         * @return error code
         */
        sm::ErrorType PrepareUpdate(sm::FunctionGroupListType const &functionGroupList);
        /**
        * @brief VerifyUpdate
        * @details Has to be called by Update And Configuration Management after State Management allowed to update
                   and the update preparation has been done. State Management will decline this request when
                   PrepareUpdate was not called before successfully.
        * @param [in] functionGroupList - The list of FunctionGroups within the SoftwareCluster to be verified.
        * @return error code
        */
        sm::ErrorType VerifyUpdate(sm::FunctionGroupListType const &functionGroupList);
        /**
        * @brief PrepareRollback
        * @details Has to be called by Update And Configuration Management after State Management allowed to update.
        * @param [in] functionGroupList - The list of FunctionGroups to be prepared to roll back.
        * @return error code
        */
        sm::ErrorType PrepareRollback(sm::FunctionGroupListType const &functionGroupList);
        /** @brief Type of request sent to SM */
        enum class RequestType {
            /** Reset Machine */
            kResetMachine,
            /** Stop Update Session */
            kStopUpdateSession,
            /** Request Update Session */
            kRequestUpdateSession,
            /** Prepare Update */
            kPrepareUpdate,
            /** Verify Update */
            kVerifyUpdate,
            /** Prepare Rollback */
            kPrepareRollback
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
        /** @brief Sends request to SM, waits for the response and returns it.
         *  @param [in] requestType - type of request sent to SM
         *  @return response from the SM */
        ara::sm::ErrorType SendRequest(RequestType requestType);
    public:
        /** @brief smRequest getter used by SM
         * @return request sent to the SM */
        RequestMsg &GetRequestMsg();

    private:
        /** @brief Contains last request return value. Set by SM in SendResponse. */
        ara::sm::ErrorType updateStatus;
    public:
        /** @brief updateStatus getter used by the SM.
         * @return updateStatus */
        [[nodiscard]] sm::ErrorType GetUpdateStatus() const;

    public:
        /** @brief SM should respond to Update Request using this function.
         *         Sets requestMsg.status flag to false, and sets updateStatus.
         *  @param [in] newUpdateStatus - return status of the Update Request. */
        void SendResponse(sm::ErrorType newUpdateStatus);

    private:
        /** @brief Update Session status set by SM */
        bool updateSession;
    public:
        /** @brief updateSession getter used by SM.
         *  @return bool updateSession. */
        [[nodiscard]] bool IsUpdateSession() const;
        /** @brief updateSession setter used by SM. */
        void SetUpdateSession(bool updateSession);

    private:
        /** @brief list being used by SM and set by PrepareUpdate/VerifyUpdate/PrepareRollback functions */
        ara::sm::FunctionGroupListType functionGroupListToSM;
    public:
        /**
         * @brief functionGroupList getter used by SM.
         * @return sm::FunctionGroupListType functionGroupList
         */
        [[nodiscard]] const ara::sm::FunctionGroupListType &GetFunctionGroupList() const;

    };
}
#endif //AUTOSAR_STATE_MANAGEMENT_UPDATE_REQUEST_H
