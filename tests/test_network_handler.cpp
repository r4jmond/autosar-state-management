#include "sm_tests.h"

/** @brief Fills [SWS_SM_00302] */
TEST_F(smTests, testNetworkHandleToFunctionGroupState) {
    mySM.myNetworkHandle.RequestStateChange(true);
    EXPECT_EQ(mySM.myNetworkHandle.NetworkState, true);
}

/** @brief Fills [SWS_SM_00303] */
TEST_F(smTests, testFunctionGroupStateToNetworkHandle) {
    mySM.myNetworkHandle.NetworkState = true;
    EXPECT_EQ(mySM.myNetworkHandle.GetNetworkState(), true);
}
