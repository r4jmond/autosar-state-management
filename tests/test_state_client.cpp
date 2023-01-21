#include "state_client.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace ara { namespace exec {
    /* Mock StateClient for unit testing. */
    class MockStateClient {
    public:
        MOCK_METHOD(void, ComSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, DiagSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, PhmSetState, (sm::FunctionGroupStateType));
        MOCK_METHOD(void, ExecSetState, (sm::FunctionGroupStateType));
    };
}}


TEST(testSuiteSM, testComSetState)
{
    ara::exec::MockStateClient MyStateClient;
    EXPECT_CALL(MyStateClient, ComSetState(ara::sm::FunctionGroupStateType::Shutdown));
    MyStateClient.ComSetState(ara::sm::FunctionGroupStateType::Shutdown);
}
