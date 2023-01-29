#include "sm_tests.h"

/** @brief Fills [SWS_SM_00021] */
TEST_F(smTests, testInternalStateInfluence) {
    mySM.triggerIn.SetTrigger(ara::sm::SMStateType::Off);
    EXPECT_EQ(mySM.triggerIn.GetDesiredState(), ara::sm::SMStateType::Off);
    EXPECT_TRUE(mySM.triggerIn.IsTrigger());
    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);
    EXPECT_FALSE(mySM.triggerIn.IsTrigger());
}


