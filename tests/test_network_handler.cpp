#include "gtest/gtest.h"
#include "state_management.h"

/** @brief Fills [SWS_SM_00302] */
TEST(testSuiteSM, testNetworkHandleToFunctionGroupState)
{
    ara::sm::StateManagement mySM;
    mySM.myNetworkHandle.RequestStateChange(true);
    EXPECT_EQ(mySM.myNetworkHandle.NetworkState, true);
}

/** @brief Fills [SWS_SM_00303] */
TEST(testSuiteSM, testFunctionGroupStateToNetworkHandle)
{
    ara::sm::StateManagement mySM;
    mySM.myNetworkHandle.NetworkState = true;
    EXPECT_EQ(mySM.myNetworkHandle.GetNetworkState(), true);
}
