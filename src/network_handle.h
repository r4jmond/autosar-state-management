#ifndef AUTOSAR_STATE_MANAGEMENT_NETWORK_HANDLE_H
#define AUTOSAR_STATE_MANAGEMENT_NETWORK_HANDLE_H

namespace ara { namespace com {
    class NetworkHandle {
    public:
        bool NetworkState;
    public:
        NetworkHandle();
        void RequestStateChange(bool);
        bool GetNetworkState() const;
    };
}}
#endif //AUTOSAR_STATE_MANAGEMENT_NETWORK_HANDLE_H