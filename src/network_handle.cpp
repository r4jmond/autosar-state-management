#include "network_handle.h"

namespace ara { namespace com {
    NetworkHandle::NetworkHandle() : NetworkState{false} {}

    void NetworkHandle::RequestStateChange(bool RequestedState) {
        NetworkState = RequestedState;
    }

    bool NetworkHandle::GetNetworkState() const {
        return NetworkState;
    }
}}