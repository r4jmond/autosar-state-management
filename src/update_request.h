#ifndef AUTOSAR_STATE_MANAGEMENT_UPDATE_REQUEST_H
#define AUTOSAR_STATE_MANAGEMENT_UPDATE_REQUEST_H
/** @file update_request.h
 * @brief Update Request SM interface to be used by UCM. */

#include "sm_types.h"

namespace ara { namespace com {
    /** @brief Class UpdateRequest to be used by Update and Configuration Management.
     *         Fills [SWS_SM_91016]. */
    class UpdateRequest {
    public:
        UpdateRequest();
        /**
        * @brief ResetMachine
        * @details Requests a reset of the machine. Before the reset is performed all information within the machine shall
                   be persisted. Request will be rejected when RequestUpdateSession was not called successfully before
        * @return error code
        */
        ara::sm::ErrorType ResetMachine();
        /**
        * @brief StopUpdateSession
        * @details Has to be called by Update And Configuration Management once the update is finished to let State
                   Management know that the update is done and the Machine is in a stable state. Request will be rejected
                   when RequestUpdateSession was not called successfully before.
        * @return error code
        */
        ara::sm::ErrorType StopUpdateSession();
        /**
         * @brief RequestUpdateSession
         * @details Has to be called by Update And Configuration Management once it has to start interaction with State
                    Management. State Management might decline this request when machine is not in a state to be
                    updated.
         * @return error code
         */
        ara::sm::ErrorType RequestUpdateSession();
        /**
         * @brief VerifyUpdate
         * @details Has to be called by Update And Configuration Management after State Management allowed to update.
                    State Management will decline this request when RequestUpdateSession was not called before
                    successfully.
         * @param[in] functionGroupList - The list of FunctionGroups within the SoftwareCluster to be prepared to be updated.
         * @return error code
         */
        ara::sm::ErrorType PrepareUpdate(sm::FunctionGroupListType functionGroupList);
//        sm::ErrorT VerifyUpdate();
//        sm::ErrorT PrepareRollback();

    private:
        bool resetRequest;
    public:
        /**
         * @brief resetRequest getter used by SM.
         * @return bool resetRequest.
         */
        bool IsResetRequest() const;

    private:
        bool resetAccepted;
    public:
        /** @brief resetAccepted setter used by SM. */
        void SetResetAccepted(bool isResetAccepted);

    private:
        /** @brief updateRequest will be set for requesting SM action.
         *         SM will interpret it based on update state.
         */
        bool updateRequest;
    public:
        /**
         * @brief updateRequest getter used by SM.
         * @return bool updateRequest.
         */
        bool IsUpdateRequest() const;
        /** @brief updateRequest setter used by SM. */
        void SetUpdateRequest(bool newUpdateRequest);

    private:
        bool updateSession;
    public:
        /**
         * @brief updateSession getter used by SM.
         * @return bool updateSession.
         */
        bool IsUpdateSession() const;
        /** @brief updateSession setter used by SM. */
        void SetUpdateSession(bool newUpdateSession);

    private:
        bool updateAccepted;
    public:
        /** @brief updateAccepted setter used by SM. */
        void SetUpdateAccepted(bool isUpdateAccepted);

    private:
        /** @brief list being used by SM and set by PrepareUpdate/VerifyUpdate/PrepareRollback functions */
        ara::sm::FunctionGroupListType functionGroupList;
    public:
        /**
         * @brief functionGroupList getter used by SM.
         * @return sm::FunctionGroupListType functionGroupList
         */
        const ara::sm::FunctionGroupListType &GetFunctionGroupList() const;

    private:
        ara::sm::ErrorType errorCode;
    public:
        /** @brief errorCode setter used by SM. */
        void SetErrorCode(ara::sm::ErrorType errorCode);

    };
}}
#endif //AUTOSAR_STATE_MANAGEMENT_UPDATE_REQUEST_H
