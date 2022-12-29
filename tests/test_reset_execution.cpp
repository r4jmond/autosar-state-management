#include "gtest/gtest.h"
#include "state_management.h"

/** @brief Fills [SWS_SM_00202] */
TEST(testSuiteSM, testResetExecution)
{
    StateManagement mySM;

    mySM.myUpdateRequest.ResetMachine();

    EXPECT_EQ(mySM.myUpdateRequest.isResetRequest(), true);
}
