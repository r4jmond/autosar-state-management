#include "state_client.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace ara { namespace exec {
    /* Mock StateClient for unit testing. */
    class MockStateClient {
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
        MOCK_METHOD(void, SmSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, TsyncSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, UcmSetState, (sm::FunctionGroupStateType));
    };
}}


TEST(testSuiteSM, testComSetState)
{
    ara::exec::MockStateClient MyStateClient;
    EXPECT_CALL(MyStateClient, ComSetState(ara::sm::FunctionGroupStateType::Shutdown));
    MyStateClient.ComSetState(ara::sm::FunctionGroupStateType::Shutdown);
}
