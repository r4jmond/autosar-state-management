#ifndef AUTOSAR_STATE_MANAGEMENT_UPDATE_REQUEST_H
#define AUTOSAR_STATE_MANAGEMENT_UPDATE_REQUEST_H

namespace ara { namespace com {
    class UpdateRequest {
    private:
        bool ongoingUpdate;
        bool resetRequest;
    public:
        bool isResetRequest() const;

    public:
        UpdateRequest();

        void ResetMachine();

        void StartUpdateSession();

        void StopUpdateSession();

        bool isOngoingUpdate() const;
    };
}}
#endif //AUTOSAR_STATE_MANAGEMENT_UPDATE_REQUEST_H
