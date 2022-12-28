#------------------------------------------------------------------------------
# Project config
#------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME autosar_state_management)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_C_FLAGS "-Wall")

#------------------------------------------------------------------------------
# Code coverage configuration
#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
include(CodeCoverage)
append_coverage_compiler_flags()
# Use command below for generating html report, then build target main_coverage
#setup_target_for_coverage_gcovr_html (
#        NAME main_coverage
#        EXECUTABLE main_test
#)

#------------------------------------------------------------------------------
# Subdirectories
#------------------------------------------------------------------------------
add_subdirectory(src)
add_subdirectory(main)

#------------------------------------------------------------------------------
# Google Test
#------------------------------------------------------------------------------
#add_subdirectory(lib/googletest)
#enable_testing()
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#SET( GTEST_LIBRARIES gtest gtest_main gmock gmock_main )
#SET( CMAKE_BUILD_TYPE Debug )
#add_subdirectory( tests )
