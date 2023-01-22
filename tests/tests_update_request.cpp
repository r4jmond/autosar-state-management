/** @file tests_update_request.cpp# Use command below for generating html report
# Build target gTests_coverage to generate html report
 * @brief Tests of the Update Request service interface.
 * @details Described in Autosar_SWS_StateManagement chapter 7.5. */

#include "sm_tests.h"

/** @brief Tests [SWS_SM_00203] - Start Update Session
 *  @details State Management shall provide the service interface UpdateRequest
 *           to Update and Configuration Management with the method call
 *           RequestUpdateSession to check if an update can be performed. (RS_SM_00100) */
TEST_F(smTests, testStartUpdateSession) {
    //todo set SM to On

    /** @test RequestUpdateSession in SM On State test */
    ara::sm::ErrorType errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test SM shall accept RequestUpdateSession in On state */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /** @test Update Session shall be true */
    EXPECT_EQ(true, mySM.myUpdateRequest.IsUpdateSession());

    // todo set SM to Off and uncomment lines below

    /** @test RequestUpdateSession in SM Off State test */
//    errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test SM shall reject RequestUpdateSession in Off state */
//    EXPECT_EQ(errorCode, ara::sm::ErrorType::kRejected);
    /** @test Update Session shall be inactive */
//    EXPECT_EQ(false, mySM.myUpdateRequest.IsUpdateSession());
}

/** @brief Tests [SWS_SM_00209] - Preventing multiple update sessions
 *  @details RequestUpdateSession shall return kNotAllowedMultipleUpdateSessions
 *          in case the method RequestUpdateSession is called during an already
 *          active Update Session. (RS_SM_00004) */
TEST_F(smTests, testMultipleUpdateSession) {

    //todo set SM to On

    /** @test RequestMultipleUpdateSession in SM On State test */
    ara::sm::ErrorType errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test SM shall accept first RequestUpdateSession in On state */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /** @test Assert that the update session is active */
    ASSERT_EQ(true, mySM.myUpdateRequest.IsUpdateSession());
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
    //todo set SM to On

    /** @test Persist Session Status test */
    /* Request update session */
    ara::sm::ErrorType errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test Assert that request Update Session is successful */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /** @test Assert that the update session is active */
    ASSERT_EQ(true, mySM.myUpdateRequest.IsUpdateSession());
    /* Restart the machine */
    errorCode = mySM.myUpdateRequest.ResetMachine();
    /** @test Assert that restart request is successful */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /** @test SM shall persist information about ongoing update session */
    EXPECT_EQ(true, mySM.myUpdateRequest.IsUpdateSession());
}

/** @brief Tests [SWS_SM_00202] - Reset execution
 *  @details State Management shall implement the service interface UpdateRequest
 *           to Update and Configuration Management with the method call
 *           ResetMachine to request a Machine reset.(RS_SM_00004) */
TEST_F(smTests, testResetExecution)
{
    //todo  Set SM to Off

    /** @test Reset Execution test */
    /* Request update session */
    ara::sm::ErrorType errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test Assert that RequestUpdateSession is successful */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    errorCode = mySM.myUpdateRequest.ResetMachine();
    /** @test SM shall accept ResetMachine request in Off state */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    //todo set SM to On

    errorCode = mySM.myUpdateRequest.ResetMachine();
    /** @test SM shall accept ResetMachine request in On state */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
}

/** @brief Tests [SWS_SM_00205] - Stop update session
 *  @details State Management shall provide the service interface UpdateRequest
 *           to Update and Configuration Management with the method call
 *           StopUpdateSession thus it can inform State Management that
 *           the update session is finished. (RS_SM_00004) */
TEST_F(smTests, testStopUpdateSession)
{
    //todo set SM to On

    /** @test StopUpdateSession test */
    /* Request update session */
    ara::sm::ErrorType errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test Assert that RequestUpdateSession is successful */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /** @test Assert that the Update Session is active */
    EXPECT_EQ(true, mySM.myUpdateRequest.IsUpdateSession());
    /* Stop update session */
    errorCode =  mySM.myUpdateRequest.StopUpdateSession();
    /** @test SM shall accept StopUpdateSession request */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /** @test Update Session shall be stopped */
    EXPECT_EQ(false, mySM.myUpdateRequest.IsUpdateSession());
}

/** @brief Tests [SWS_SM_00206] - Prepare update
 *  @details State Management shall provide the service interface
 *           UpdateRequest to Update and Configuration Management
 *           with the method call PrepareUpdate thus it can request
 *           State Management to perform a preparation of the given
 *           Function Groups to be updated. (RS_SM_00004) */
TEST_F(smTests, testPrepareUpdate)
{
    //todo set SM to On

    ara::sm::FunctionGroupListType testFGList {
            ara::sm::FunctionGroupNameType::sm,
            ara::sm::FunctionGroupNameType::exec,
            ara::sm::FunctionGroupNameType::phm,
            ara::sm::FunctionGroupNameType::ucm
    };

    /** @test PrepareUpdate request without active Update Session test */
    ara::sm::ErrorType errorCode =  mySM.myUpdateRequest.PrepareUpdate(testFGList);
    /** @test SM Shall reject that request */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kRejected);

    /** @test PrepareUpdate test */
    /* Request update session */
    errorCode =  mySM.myUpdateRequest.RequestUpdateSession();
    /** @test Assert that RequestUpdateSession is successful */
    ASSERT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
    /* Prepare update */
    errorCode =  mySM.myUpdateRequest.PrepareUpdate(testFGList);
    /** @test SM shall accept PrepareUpdate Request */
    EXPECT_EQ(errorCode, ara::sm::ErrorType::kSuccess);
}

/** @brief Tests [SWS_SM_00207] - Verify update
 *  @details State Management shall provide the service interface UpdateRequest
 *           to Update and Configuration Management with the method call VerifyUpdate
 *           thus it can request State Management to perform a verification of the
 *           given Function Groups. (RS_SM_00004) */
TEST_F(smTests, testVerifyUpdate)
{
    //todo set SM to On

    ara::sm::FunctionGroupListType testFGList {
            ara::sm::FunctionGroupNameType::sm,
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
//    GTEST_SKIP() << "temp skip test";
    //todo set SM to On

    ara::sm::FunctionGroupListType testFGList {
            ara::sm::FunctionGroupNameType::sm,
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
    /** @test Send Prepare update request with eroneous data */
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
