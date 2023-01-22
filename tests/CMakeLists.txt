#------------------------------------------------------------------------------
# Unit Tests
#------------------------------------------------------------------------------
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable( gTests_all
        tests.cpp
        sm_tests.h
        tests_update_request.cpp
        test_network_handler.cpp
        sm_tests.h)

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