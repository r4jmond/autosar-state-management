#ifndef AUTOSAR_STATE_MANAGEMENT_SM_TESTS_H
#define AUTOSAR_STATE_MANAGEMENT_SM_TESTS_H
/** @file sm_tests.h
 * @brief Header with text fixture and basic includes for SM tests.
 * @details Should be included by SM tests.. */

#include <thread>
#include "state_management.h"
#include "mocks/mock_state_client.h"
#include "sm_types.h"
#include "gtest/gtest.h"

/**
 * @brief Text fixture for SM tests.
 * @details Runs SM in another thread, and kills it after the test.
 */
class smTests : public testing::Test {
protected:
    ara::exec::MockStateClient mySC;
    ara::sm::StateManagement mySM;
    std::thread smThread;
    smTests() : mySC{ara::exec::MockStateClient()}, mySM{ara::sm::StateManagement(&mySC)} {
        smThread = std::thread(&ara::sm::StateManagement::Work, &mySM);
    }
    ~smTests() override {
        mySM.Kill();
        smThread.join();
    }
};

#endif //AUTOSAR_STATE_MANAGEMENT_SM_TESTS_H
