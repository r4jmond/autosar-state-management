#include "gtest/gtest.h"
#include "sm_types.h"
#include <string>
#include "recovery_action.h"

/** @brief Fills [SWS_SM_00202] */

using namespace ara;
TEST(testSuiteSM, testRecoveryAction)
{
   std::string type = "";
   bool errorOcurredTest;
   phm::RecoveryAction<std::string> recoveryAction;
   errorOcurredTest = recoveryAction.recoveryActionHandler(&type);
   EXPECT_EQ(errorOcurredTest, false);
}
