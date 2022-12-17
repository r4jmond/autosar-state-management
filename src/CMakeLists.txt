#------------------------------------------------------------------------------
# Autosar state management
#------------------------------------------------------------------------------

set(SRCS
        Employee.h
        Employee.cpp
        )

add_library(src STATIC ${SRCS})

target_include_directories(src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
