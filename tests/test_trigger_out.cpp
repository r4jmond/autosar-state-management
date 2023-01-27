#include "sm_tests.h"

/** @brief Fills [SWS_SM_00020] */
TEST_F(smTests, testInternalStatePropagation) {
    mySM.triggerOut.SetNotifier(ara::sm::SMStateType::On);
    EXPECT_EQ(mySM.triggerOut.GetSMState(), ara::sm::SMStateType::On);
}
