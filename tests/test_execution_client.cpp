#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "sm_tests.h"

namespace ara::exec {
    /* Mock ExecutionClient for unit testing. */
    class MockExecutionClient : public ExecutionClient {
    public:
        MOCK_METHOD(void, ReportApplicationState, (sm::FunctionGroupStateType state));
    };
}

TEST_F(smTests,  testExecutionClient)
{
    ara::exec::MockExecutionClient mockEC;
    mySM.executionClient = &mockEC;
    EXPECT_CALL(mockEC,
                ReportApplicationState(ara::sm::FunctionGroupStateType::On)).Times(testing::AnyNumber());

    mySM.stateClient->SmSetState(ara::sm::FunctionGroupStateType::On);

    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);

    // due to possible GTest stuck while expecting a call
    mySM.Kill();
}