#------------------------------------------------------------------------------
# Project config
#------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME MyProject)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_C_FLAGS "-g -Wall")

#------------------------------------------------------------------------------
# Normal Libraries and Executables
#------------------------------------------------------------------------------
add_library(src
        src/Employee.cpp
        src/Employee.h
        )
add_executable( main_noTest
        main/main.cpp
        )

include_directories(src/)

target_link_libraries(main_noTest src)

#------------------------------------------------------------------------------
# Testing
#------------------------------------------------------------------------------
if (test)
    add_subdirectory(lib/googletest)

    enable_testing()

    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    SET( GTEST_LIBRARIES gtest gtest_main gmock gmock_main )
    SET( CMAKE_BUILD_TYPE Debug )

    include( cmake_modules/CodeCoverage.cmake )
    SET(CMAKE_CXX_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")

    add_subdirectory( tests )

endif()
