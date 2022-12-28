#------------------------------------------------------------------------------
# Autosar state management
#------------------------------------------------------------------------------

set(SRCS
        Employee.h
        Employee.cpp
        )

add_library(Autosar_SM ${SRCS})
target_include_directories(Autosar_SM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
