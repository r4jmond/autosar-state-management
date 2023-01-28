#include "sm_tests.h"

/** @brief Fills [SWS_SM_00020] */
TEST_F(smTests, testInternalStatePropagation) {
    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);
    EXPECT_EQ(mySM.triggerOut.GetNotifier(), ara::sm::SMStateType::On);
}
