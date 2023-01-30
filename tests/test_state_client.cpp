
#include "sm_tests.h"


TEST_F(smTests, testComSetState)
{
    EXPECT_CALL(mySC, SetState(ara::sm::FunctionGroupNameType::com,
                                        ara::sm::FunctionGroupStateType::Off));
    mySC.SetState(ara::sm::FunctionGroupNameType::com,ara::sm::FunctionGroupStateType::Off);
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
    EXPECT_CALL(mySC, undefinedStateCallback);

    EXPECT_EQ(mySM.internalState, ara::sm::FunctionGroupStateType::Off);
    mySM.stateClient->SmSetState((ara::sm::FunctionGroupStateType) ara::sm::MachineStateType::Restart);
    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);
    EXPECT_EQ(mySM.internalState, ara::sm::FunctionGroupStateType::Off);
}

TEST_F(smTests, testInitialStateTransitionResultSuccess)
{
    mySM.stateClient->SetInitialMachineStateTransitionResult(ara::sm::ErrorType::kSuccess);
    // let changes to be applied
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);
    EXPECT_EQ(mySM.internalState, ara::sm::FunctionGroupStateType::On);
}
