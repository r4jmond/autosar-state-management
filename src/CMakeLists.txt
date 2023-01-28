#------------------------------------------------------------------------------
# Autosar state management
#------------------------------------------------------------------------------

set(SRCS
        state_management.cpp
        state_management.h
        trigger_in.cpp
        trigger_in.h
        update_request.cpp
        update_request.h
        trigger_out.cpp
        trigger_out.h
        trigger_in_out.cpp
        trigger_in_out.h
        network_handle.cpp
        network_handle.h
        state_client.h
        sm_types.h
        state_client.cpp
        execution_client.h
        execution_client.cpp)

add_library(Autosar_SM ${SRCS})
target_include_directories(Autosar_SM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
