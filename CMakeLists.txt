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

#------------------------------------------------------------------------------
# Subdirectories
#------------------------------------------------------------------------------
add_subdirectory(src)
add_subdirectory(main)

#------------------------------------------------------------------------------
# Google Test
#------------------------------------------------------------------------------
# SET( CMAKE_BUILD_TYPE Debug )
# idk if this commented line above may be necessary for some reason, for now leaving it
add_subdirectory(lib/googletest)
add_subdirectory(tests)
