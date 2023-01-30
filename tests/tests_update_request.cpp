/** @file tests_update_request.cpp
 * @brief Tests of the Update Request service interface.
 * @details Described in Autosar_SWS_StateManagement chapter 7.5. */

#include "sm_tests.h"

using namespace std::chrono_literals;

/** @brief Tests [SWS_SM_00203] - Start Update Session
 *  @details State Management shall provide the service interface UpdateRequest
 *           to Update and Configuration Management with the method call
 *           RequestUpdateSession to check if an update can be performed. (RS_SM_00100) */
TEST_F(smTests, testStartUpdateSession) {

    /** @test RequestUpdateSession in SM On State test */
    /** Set SM to ON */
    mySC.SmSetState(ara::sm::FunctionGroupStateType::On);
    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    auto notifier = mySM.triggerOut.GetNotifier();
    /** Assert that the SM is on */
    ASSERT_EQ(notifier, ara::sm::FunctionGroupStateType::On);

    ara::sm::ErrorType errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test SM shall accept RequestUpdateSession in On state */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kSuccess);

    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    /** @test SM shall be in Update State */
    EXPECT_EQ(ara::sm::FunctionGroupStateType::Update, mySM.triggerOut.GetNotifier());


    /** @test RequestUpdateSession in SM Off State test */
    /** Set SM to Off */
    mySC.SmSetState(ara::sm::FunctionGroupStateType::Off);
    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    notifier = mySM.triggerOut.GetNotifier();
    /** Assert that the SM is off */
    ASSERT_EQ(notifier, ara::sm::FunctionGroupStateType::Off);

    errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test SM shall reject RequestUpdateSession in Off state */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kRejected);
}

/** @brief Tests [SWS_SM_00209] - Preventing multiple update sessions
 *  @details RequestUpdateSession shall return kNotAllowedMultipleUpdateSessions
 *          in case the method RequestUpdateSession is called during an already
 *          active Update Session. (RS_SM_00004) */
TEST_F(smTests, testMultipleUpdateSession) {

    /** @test RequestMultipleUpdateSession in SM On State test */
    /** Set SM to ON */
    mySC.SmSetState(ara::sm::FunctionGroupStateType::On);
    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    auto notifier = mySM.triggerOut.GetNotifier();
    /** Assert that the SM is on */
    ASSERT_EQ(notifier, ara::sm::FunctionGroupStateType::On);

    ara::sm::ErrorType errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test SM shall accept first RequestUpdateSession in On state */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);

    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    /** @test Assert that the SM is in Update State */
    ASSERT_EQ(ara::sm::FunctionGroupStateType::Update, mySM.triggerOut.GetNotifier());

    /* Request another update session */
    errorCode = mySM.myUpdateRequest.RequestUpdateSession();
    /** @test SM shall reject RequestUpdateSession if it is called during
     *        already active Update Session. */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kNotAllowedMultipleUpdateSessions);
}

/** @brief Tests [SWS_SM_00204] - Persist session status
 *  @details State Management shall persist information about ongoing update session,
 *           thus it can be read out after any kind of Machine reset.(RS_SM_00004) */
TEST_F(smTests, testPersistSessionStatus) {
    /** @test Persist Session Status test */
    /** Set SM to ON */
    mySC.SmSetState(ara::sm::FunctionGroupStateType::On);
    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    auto notifier = mySM.triggerOut.GetNotifier();
    /** Assert that the SM is on */
    ASSERT_EQ(notifier, ara::sm::FunctionGroupStateType::On);

    /* Request update session */
    ara::sm::ErrorType errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test Assert that request Update Session is successful */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);

    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    /** @test Assert that the SM is in Update State */
    ASSERT_EQ(ara::sm::FunctionGroupStateType::Update, mySM.triggerOut.GetNotifier());

    /* Restart the machine */
    errorCode = mySM.myUpdateRequest.ResetMachine();
    /** @test Assert that restart request is successful */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);

    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    notifier = mySM.triggerOut.GetNotifier();
    /** @test SM shall be in update state after restart - it shall persist information about ongoing update session */
    EXPECT_EQ(notifier, ara::sm::FunctionGroupStateType::Update);
}

/** @brief Tests [SWS_SM_00202] - Reset execution
 *  @details State Management shall implement the service interface UpdateRequest
 *           to Update and Configuration Management with the method call
 *           ResetMachine to request a Machine reset.(RS_SM_00004) */
TEST_F(smTests, testResetExecution)
{
    EXPECT_CALL(mySC,
                MachineSetState(ara::sm::MachineStateType::Restart)
                ).Times(testing::AnyNumber());

    /** Set SM to ON */
    mySC.SmSetState(ara::sm::FunctionGroupStateType::On);
    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    auto notifier = mySM.triggerOut.GetNotifier();
    /** Assert that the SM is on */
    ASSERT_EQ(notifier, ara::sm::FunctionGroupStateType::On);

    /** @test ResetMachine request without active UpdateSession shall be rejected */
    auto errorCode = mySM.myUpdateRequest.ResetMachine();
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kRejected);

    /** @test RequestUpdateSession shall be accepted */
    errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** SM shall accept RequestUpdateSession in On state */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);

    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    /** @test Assert that the SM is in Update State */
    ASSERT_EQ(ara::sm::FunctionGroupStateType::Update, mySM.triggerOut.GetNotifier());
    /** @test ResetMachine request with active UpdateSession shall be accepted */
    errorCode = mySM.myUpdateRequest.ResetMachine();
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
}

/** @brief Tests [SWS_SM_00205] - Stop update session
 *  @details State Management shall provide the service interface UpdateRequest
 *           to Update and Configuration Management with the method call
 *           StopUpdateSession thus it can inform State Management that
 *           the update session is finished. (RS_SM_00004) */
TEST_F(smTests, testStopUpdateSession)
{
    /** Set SM to ON */
    mySC.SmSetState(ara::sm::FunctionGroupStateType::On);
    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    auto notifier = mySM.triggerOut.GetNotifier();
    /** Assert that the SM is on */
    ASSERT_EQ(notifier, ara::sm::FunctionGroupStateType::On);

    /** @test Stop update request shall be rejected without active update session */
    auto errorCode =  mySM.myUpdateRequest.StopUpdateSession();
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kRejected);

    /** @test StopUpdateSession test with active UpdateSession */
    /* Request update session */
    errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test Assert that RequestUpdateSession is successful */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);

    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    /** @test Assert that the SM is in Update State */
    ASSERT_EQ(ara::sm::FunctionGroupStateType::Update, mySM.triggerOut.GetNotifier());

    /* Stop update session */
    errorCode =  mySM.myUpdateRequest.StopUpdateSession();
    /** @test SM shall accept StopUpdateSession request */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    /** @test Update Session shall be stopped */
    ASSERT_EQ(ara::sm::FunctionGroupStateType::On, mySM.triggerOut.GetNotifier());
}

/** @brief Tests [SWS_SM_00206] - Prepare update
 *  @details State Management shall provide the service interface
 *           UpdateRequest to Update and Configuration Management
 *           with the method call PrepareUpdate thus it can request
 *           State Management to perform a preparation of the given
 *           Function Groups to be updated. (RS_SM_00004) */
TEST_F(smTests, testPrepareUpdate)
{
    /** Set SM to ON */
    mySC.SmSetState(ara::sm::FunctionGroupStateType::On);
    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    auto notifier = mySM.triggerOut.GetNotifier();
    /** Assert that the SM is on */
    ASSERT_EQ(notifier, ara::sm::FunctionGroupStateType::On);

    ara::sm::FunctionGroupListType testFGList {
            ara::sm::FunctionGroupNameType::exec,
            ara::sm::FunctionGroupNameType::phm,
            ara::sm::FunctionGroupNameType::ucm
    };

    /** @test PrepareUpdate request without active Update Session test shall be rejected */
    ara::sm::ErrorType errorCode =  mySM.myUpdateRequest.PrepareUpdate(testFGList);
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kRejected);

    /** @test PrepareUpdate test with active update session */
    /* Request update session */
    errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test Assert that RequestUpdateSession is successful */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    /** @test Assert that the SM is in Update State */
    ASSERT_EQ(ara::sm::FunctionGroupStateType::Update, mySM.triggerOut.GetNotifier());

    /* Prepare update */
    errorCode =  mySM.myUpdateRequest.PrepareUpdate(testFGList);
    /** @test SM shall accept PrepareUpdate Request */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kSuccess);

    /** @test Prepare Update request with erroneous data shall fail */
    ara::sm::FunctionGroupListType erroneousFGList {
            ara::sm::FunctionGroupNameType::log
    };
    errorCode =  mySM.myUpdateRequest.PrepareUpdate(erroneousFGList);
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kFailed);
}

/** @brief Tests [SWS_SM_00207] - Verify update
 *  @details State Management shall provide the service interface UpdateRequest
 *           to Update and Configuration Management with the method call VerifyUpdate
 *           thus it can request State Management to perform a verification of the
 *           given Function Groups. (RS_SM_00004) */
TEST_F(smTests, testVerifyUpdate)
{
    /** Set SM to ON */
    mySC.SmSetState(ara::sm::FunctionGroupStateType::On);
    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    auto notifier = mySM.triggerOut.GetNotifier();
    /** Assert that the SM is on */
    ASSERT_EQ(notifier, ara::sm::FunctionGroupStateType::On);

    ara::sm::FunctionGroupListType testFGList {
            ara::sm::FunctionGroupNameType::exec,
            ara::sm::FunctionGroupNameType::phm,
            ara::sm::FunctionGroupNameType::ucm
    };

    /** @test VerifyUpdate without active UpdateSession test */
    ara::sm::ErrorType errorCode = mySM.myUpdateRequest.VerifyUpdate(testFGList);
    /** @test SM shall reject that request */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kRejected);

    /** @test VerifyUpdate test */
    /* Request update session */
    errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test Assert that RequestUpdateSession is successful */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    /** @test Assert that the SM is in Update State */
    ASSERT_EQ(ara::sm::FunctionGroupStateType::Update, mySM.triggerOut.GetNotifier());

    /* Prepare update */
    errorCode =  mySM.myUpdateRequest.PrepareUpdate(testFGList);
    /** @test SM shall accept PrepareUpdate Request */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /* Verify update */
    errorCode = mySM.myUpdateRequest.VerifyUpdate(testFGList);
    /** @test SM shall accept VerifyUpdate request */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
}

/** @brief Tests [SWS_SM_00208] - Prepare rollback
 *  @details State Management shall provide the service interface
 *           UpdateRequest to Update and Configuration Management
 *           with the method call PrepareRollback thus it can request
 *           State Management to perform a preparation of the given
 *           Function Groups to be rolled back. (RS_SM_00004) */
TEST_F(smTests, testPrepareRollback)
{
    /** Set SM to ON */
    mySC.SmSetState(ara::sm::FunctionGroupStateType::On);
    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    auto notifier = mySM.triggerOut.GetNotifier();
    /** Assert that the SM is on */
    ASSERT_EQ(notifier, ara::sm::FunctionGroupStateType::On);

    ara::sm::FunctionGroupListType testFGList {
            ara::sm::FunctionGroupNameType::exec,
            ara::sm::FunctionGroupNameType::phm,
            ara::sm::FunctionGroupNameType::ucm
    };

    /** @test PrepareRollback without active UpdateSession test */
    /* Prepare Rollback */
    ara::sm::ErrorType errorCode = mySM.myUpdateRequest.PrepareRollback(testFGList);
    /** @test SM shall reject Prepare Rollback request */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kRejected);

    /** @test PrepareRollback without error test */
    /* Request update session */
    errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test Assert that RequestUpdateSession is successful */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /** wait for the changes to propagate */
    std::this_thread::sleep_for(20ms);
    /** @test Assert that the SM is in Update State */
    ASSERT_EQ(ara::sm::FunctionGroupStateType::Update, mySM.triggerOut.GetNotifier());
    /* Prepare update */
    errorCode =  mySM.myUpdateRequest.PrepareUpdate(testFGList);
    /** @test Assert that SM accepted PrepareUpdate Request */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /* Verify update */
    errorCode = mySM.myUpdateRequest.VerifyUpdate(testFGList);
    /** @test SM shall accept verifyUpdate request */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /* Prepare Rollback */
    errorCode = mySM.myUpdateRequest.PrepareRollback(testFGList);
    /** @test SM shall reject Prepare Rollback request */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kRejected);

    /** @test PrepareRollback test */
    /** @test Send Prepare update request with erroneous data */
    ara::sm::FunctionGroupListType erroneousFGList {
        ara::sm::FunctionGroupNameType::log
    };
    errorCode =  mySM.myUpdateRequest.PrepareUpdate(erroneousFGList);
    /** @test Assert that SM failed PrepareUpdate */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kFailed);
    /* Prepare Rollback */
    errorCode = mySM.myUpdateRequest.PrepareRollback(testFGList);
    /** @test SM shall accept Prepare Rollback request */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
}
