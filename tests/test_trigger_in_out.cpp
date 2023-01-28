#include "sm_tests.h"


/** @brief Fills [SWS_SM_00020]
 *         Fills [SWS_SM_00021] */
TEST_F(smTests, testInternalStateInfluenceAndPropagation) {
    mySM.triggerInOut.SetTrigger(ara::sm::SMStateType::On);
    EXPECT_TRUE(mySM.triggerInOut.IsTrigger());

    // let changes to be applied
    sleep(1);

    ara::sm::TriggerInOutNotifierType executionResult = mySM.triggerInOut.GetNotifier();
    EXPECT_EQ(executionResult.currentSMState, ara::sm::SMStateType::On);
    EXPECT_EQ(executionResult.result, ara::sm::ErrorType::kSuccess);
    EXPECT_FALSE(mySM.triggerInOut.IsTrigger());
}
