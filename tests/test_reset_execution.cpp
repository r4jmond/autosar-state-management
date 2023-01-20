#include "gtest/gtest.h"
#include "sm_types.h"
#include "state_management.h"

/** @brief Fills [SWS_SM_00202] */
TEST(testSuiteSM, testResetExecution)
{
    ara::sm::StateManagement mySM;

    ara::sm::ErrorType retVal = mySM.myUpdateRequest.ResetMachine();

    EXPECT_EQ(retVal, ara::sm::ErrorType::kSuccess);
}
