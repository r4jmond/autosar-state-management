#include "sm_tests.h"

/** @brief Fills SWS_Platform_Health_Management] */
TEST_F(smTests, testRecoveryAction)
{
    std::string retVal;
    bool errorStatus;

    errorStatus = mySM.recoveryAction.recoveryActionHandler(&retVal);
    EXPECT_EQ(errorStatus, false);


    retVal = "error occurred";
    mySM.recoveryAction.raiseError(&retVal);
    retVal = "";

    errorStatus = mySM.recoveryAction.recoveryActionHandler(&retVal);
    EXPECT_EQ(errorStatus, true);
    EXPECT_EQ(retVal, "error occurred");


    errorStatus = mySM.recoveryAction.recoveryActionHandler(&retVal);
    EXPECT_EQ(errorStatus, false);
}
