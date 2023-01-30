#include "sm_tests.h"

/** @brief Fills SWS_Platform_Health_Management] */
TEST_F(smTests, testRecoveryAction){
    std::string retVal;
    bool errorStatus;

    /** @test Check if default error state is false */
    errorStatus = mySM.recoveryAction.RecoveryActionHandler(&retVal);
    EXPECT_EQ(errorStatus, false);

    /** @test Report error and check if its possible to read it*/
    retVal = "error occurred";
    /** report error */
    mySM.recoveryAction.RaiseError(&retVal);
    retVal = "";

    /** try to read error and check if error message is correct */
    errorStatus = mySM.recoveryAction.RecoveryActionHandler(&retVal);
    EXPECT_EQ(errorStatus, true);
    EXPECT_EQ(retVal, "error occurred");

    /** @test Check if error status is cleared */
    errorStatus = mySM.recoveryAction.RecoveryActionHandler(&retVal);
    EXPECT_EQ(errorStatus, false);
}
