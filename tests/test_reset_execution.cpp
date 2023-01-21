#include "gtest/gtest.h"
#include "tests.h"

/** @brief Fills [SWS_SM_00202] */
TEST_F(smTests, testResetExecution)
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);

    ara::sm::ErrorType retVal = mySM.myUpdateRequest.ResetMachine();
    EXPECT_EQ(retVal, ara::sm::ErrorType::kSuccess);
}
