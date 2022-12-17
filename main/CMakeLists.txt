#------------------------------------------------------------------------------
# App execution
#------------------------------------------------------------------------------

set(Main_SRCS main.cpp)

add_executable(myApp ${Main_SRCS})

target_link_libraries(myApp src)

install(TARGETS myApp DESTINATION bin)
