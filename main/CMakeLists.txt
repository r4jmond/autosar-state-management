#------------------------------------------------------------------------------
# App execution
#------------------------------------------------------------------------------

add_executable(main_test main.cpp)
target_link_libraries(main_test Autosar_SM)
# install(TARGETS myApp DESTINATION bin)
# idk if this commented line above may be necessary for some reason, for now leaving it
