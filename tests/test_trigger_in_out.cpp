#include "sm_tests.h"


/** @brief Fills [SWS_SM_00020]
 *         Fills [SWS_SM_00021] */
TEST_F(smTests, testInternalStateInfluenceAndPropagation) {
    mySM.triggerInOut.SetTrigger(ara::sm::FunctionGroupStateType::On);
    EXPECT_TRUE(mySM.triggerInOut.IsTrigger());

    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);

    ara::sm::TriggerInOutNotifierType executionResult = mySM.triggerInOut.GetNotifier();
    EXPECT_EQ(executionResult.currentSMState, ara::sm::FunctionGroupStateType::On);
    EXPECT_EQ(executionResult.result, ara::sm::ErrorType::kSuccess);
    EXPECT_FALSE(mySM.triggerInOut.IsTrigger());
}
