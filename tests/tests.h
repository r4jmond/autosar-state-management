#include <thread>
#include "state_management.h"
#include "sm_types.h"
#include "gtest/gtest.h"

class smTests : public testing::Test {
protected:
    ara::sm::StateManagement mySM;
    std::thread smThread;
    smTests(){
        smThread = std::thread(&ara::sm::StateManagement::Work, &mySM);
    }
    ~smTests() override {
        mySM.Kill();
        smThread.join();
    }
};

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
