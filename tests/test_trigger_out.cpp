#include "sm_tests.h"

/** @brief Fills [SWS_SM_00020] */
TEST_F(smTests, testInternalStatePropagation) {
    // let changes to be applied
    sleep(1);
    EXPECT_EQ(mySM.triggerOut.GetNotifier(), ara::sm::SMStateType::On);
}
