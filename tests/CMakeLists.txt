#------------------------------------------------------------------------------
# Unit Tests
#------------------------------------------------------------------------------
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable( gTests_all
        tests.cpp
        sm_tests.h
        tests_update_request.cpp
        test_state_client.cpp
        test_network_handler.cpp
        test_trigger_in.cpp
        test_trigger_out.cpp
        test_trigger_in_out.cpp
        mocks/mock_state_client.h
        test_ecu_reset_request.cpp
        test_execution_client.cpp
        test_communication_group_server.cpp
        test_recovery_action.cpp
        mocks/mock_execution_client.h
        mocks/mock_state_client.h)


SET( GTEST_LIBRARIES gtest gtest_main gmock gmock_main )
target_link_libraries( gTests_all ${GTEST_LIBRARIES} )
target_link_libraries( gTests_all Autosar_SM )

# Use command below for generating html report
# Build target gTests_coverage to generate html report
setup_target_for_coverage_gcovr_html (
        NAME gTests_coverage
        EXECUTABLE gTests_all
        EXCLUDE lib/ main/
)