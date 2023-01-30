#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "state_client.h"


namespace ara::exec {
    /* Mock StateClient for unit testing. */
    class MockStateClient : public StateClient {
    public:
        MOCK_METHOD(ExecErrc, SetState, (std::string fgName, sm::FunctionGroupStateType fgState));
        MOCK_METHOD(ExecErrc, MachineSetState, (sm::MachineStateType machineState));
        MOCK_METHOD(void, undefinedStateCallback, ());
    };
}
