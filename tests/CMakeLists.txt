#------------------------------------------------------------------------------
# Unit Tests
#------------------------------------------------------------------------------

set( BIN_NAME testSuite )

add_executable( ${BIN_NAME}
        main.cpp
        test_Employee.cpp
        )

target_link_libraries( ${BIN_NAME} ${GTEST_LIBRARIES} )
target_link_libraries( ${BIN_NAME} src )

SETUP_TARGET_FOR_COVERAGE(
        coverage_${BIN_NAME}
        ${BIN_NAME}
        coverage_report
)
