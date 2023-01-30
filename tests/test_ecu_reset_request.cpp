/** @file tests_ecu_reset_request.cpp
 * @brief Tests of the ECU Reset Request interface.
 * @details Described in Autosar_SWS_StateManagement chapter 7.4. */

#include "sm_tests.h"

using namespace std::chrono_literals;


TEST_F(smTests, enableRapidShutdown) {
    mySM.ecuResetRequest.EnableRapidShutdown();
    std::this_thread::sleep_for(20ms);
    EXPECT_EQ(mySM.GetShutdownFlag(), true);
}

TEST_F(smTests, disableRapidShutdown) {
    mySM.ecuResetRequest.EnableRapidShutdown();
    std::this_thread::sleep_for(20ms);
    ASSERT_EQ(mySM.GetShutdownFlag(), true);

    mySM.ecuResetRequest.DisableRapidShutdown();
    std::this_thread::sleep_for(20ms);
    EXPECT_EQ(mySM.GetShutdownFlag(), false);
}

TEST_F(smTests, executeReset) {
    EXPECT_CALL(mySC, MachineSetState(ara::sm::MachineStateType::Restart));

    mySM.ecuResetRequest.ExecuteReset();
    std::this_thread::sleep_for(20ms);
}
