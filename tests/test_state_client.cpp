#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "sm_tests.h"

namespace ara::exec {
    /* Mock StateClient for unit testing. */
    class MockStateClient : public StateClient {
    public:
        MOCK_METHOD(void, CoreSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, ComSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, CryptoSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, DiagSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, ExecSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, FwSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, IamSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, IdsmSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, LogSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, NmSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, NaSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, PerSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, PhmSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, TsyncSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, UcmSetState, (sm::FunctionGroupStateType));
    };
}


TEST(testSuiteSM, testComSetState)
{
    ara::exec::MockStateClient MyStateClient;
    EXPECT_CALL(MyStateClient, ComSetState(ara::sm::FunctionGroupStateType::Shutdown));
    MyStateClient.ComSetState(ara::sm::FunctionGroupStateType::Shutdown);
}

TEST_F(smTests, testSMSetStateOn)
{
    EXPECT_EQ(mySM.internalState, ara::sm::SMStateType::Off);
    mySM.stateClient->SmSetState(ara::sm::FunctionGroupStateType::On);
    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);
    EXPECT_EQ(mySM.internalState, ara::sm::SMStateType::On);
}

TEST_F(smTests, testSMSetStateOff)
{
    mySM.stateClient->SmSetState(ara::sm::FunctionGroupStateType::Off);
    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);
    EXPECT_EQ(mySM.internalState, ara::sm::SMStateType::Off);
}

TEST_F(smTests, testSMSetStateUndefined)
{
    EXPECT_EQ(mySM.internalState, ara::sm::SMStateType::Off);
    mySM.stateClient->SmSetState(ara::sm::FunctionGroupStateType::Startup);
    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);
    EXPECT_EQ(mySM.internalState, ara::sm::SMStateType::Off);
}
