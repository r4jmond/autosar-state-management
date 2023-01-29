#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "sm_tests.h"

namespace ara::exec {
    /* Mock StateClient for unit testing. */
    class MockStateClient : public StateClient {
    public:
        MOCK_METHOD(ExecErrc, SetState, (std::string fgName, sm::FunctionGroupStateType fgState));
    };
}


TEST_F(smTests, testComSetState)
{
    ara::exec::MockStateClient MyStateClient;
    EXPECT_CALL(MyStateClient, SetState(ara::sm::FunctionGroupNameType::com,
                                        ara::sm::FunctionGroupStateType::Off));
    MyStateClient.SetState(ara::sm::FunctionGroupNameType::com, ara::sm::FunctionGroupStateType::Off);
}

TEST_F(smTests, testSMSetStateOn)
{
    EXPECT_EQ(mySM.internalState, ara::sm::FunctionGroupStateType::Off);
    mySM.stateClient->SmSetState(ara::sm::FunctionGroupStateType::On);
    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);
    EXPECT_EQ(mySM.internalState, ara::sm::FunctionGroupStateType::On);
}

TEST_F(smTests, testSMSetStateOff)
{
    mySM.stateClient->SmSetState(ara::sm::FunctionGroupStateType::Off);
    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);
    EXPECT_EQ(mySM.internalState, ara::sm::FunctionGroupStateType::Off);
}

TEST_F(smTests, testSMSetStateUndefined)
{
    EXPECT_EQ(mySM.internalState, ara::sm::FunctionGroupStateType::Off);
    mySM.stateClient->SmSetState((ara::sm::FunctionGroupStateType) ara::sm::MachineStateType::Startup);
    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);
    EXPECT_EQ(mySM.internalState, ara::sm::FunctionGroupStateType::Off);
}
