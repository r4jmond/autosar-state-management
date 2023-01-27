#include "sm_tests.h"


/** @brief Fills [SWS_SM_00020]
 *         Fills [SWS_SM_00021] */
TEST_F(smTests, testInternalStateInfluenceAndPropagation) {
    mySM.triggerInOut.SetSMState(ara::sm::SMStateType::On);

    // SM part
    EXPECT_TRUE(mySM.triggerInOut.IsTrigger());
    mySM.triggerInOut.SetTransitionResult(ara::sm::ErrorType::kSuccess, ara::sm::SMStateType::On);
    mySM.triggerInOut.DiscardTrigger();

    ara::sm::TriggerInOutNotifierType executionResult = mySM.triggerInOut.GetTransitionResult();
    EXPECT_EQ(executionResult.currentSMState, ara::sm::SMStateType::On);
    EXPECT_EQ(executionResult.result, ara::sm::ErrorType::kSuccess);
    EXPECT_FALSE(mySM.triggerInOut.IsTrigger());
}


