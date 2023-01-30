#ifndef AUTOSAR_STATE_MANAGEMENT_MOCK_EXECUTION_CLIENT_H
#define AUTOSAR_STATE_MANAGEMENT_MOCK_EXECUTION_CLIENT_H


#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "execution_client.h"

namespace ara::exec {
    /* Mock ExecutionClient for unit testing. */
    class MockExecutionClient : public ExecutionClient {
    public:
        MOCK_METHOD(void, ReportApplicationState, (sm::FunctionGroupStateType state));
    };
}

#endif //AUTOSAR_STATE_MANAGEMENT_MOCK_EXECUTION_CLIENT_H
