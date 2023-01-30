#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "sm_tests.h"


TEST_F(smTests,  testExecutionClientOn)
{
    EXPECT_CALL(myEC,
                ReportApplicationState(ara::sm::FunctionGroupStateType::On)).
                Times(testing::AnyNumber());

    mySM.stateClient->SmSetState(ara::sm::FunctionGroupStateType::On);

    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);

    // due to possible GTest stuck while expecting a call
    mySM.Kill();
}

TEST_F(smTests,  testExecutionClientOff)
{
    EXPECT_CALL(myEC,
                ReportApplicationState(ara::sm::FunctionGroupStateType::Off)).
                Times(testing::AnyNumber());

    mySM.stateClient->SmSetState(ara::sm::FunctionGroupStateType::Off);

    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);

    // due to possible GTest stuck while expecting a call
    mySM.Kill();
}
