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
        sm_types.h
        execution_client.h
        contains.h
        state_client.h
        state_client.cpp
        ecu_reset_request.h
        ecu_reset_request.cpp
        recovery_action.h
        power_mode.cpp
        power_mode.h
        communication_group_server.h
        diagnostic_reset.cpp
        diagnostic_reset.h)

add_library(Autosar_SM ${SRCS})
target_include_directories(Autosar_SM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
