#include "sm_tests.h"

TEST_F(smTests, testExecutionClient)
{
    mySM.stateClient->SmSetState(ara::sm::FunctionGroupStateType::On);
    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);
    EXPECT_EQ(mySM.executionClient->GetApplicationState(), ara::sm::SMStateType::On);
}