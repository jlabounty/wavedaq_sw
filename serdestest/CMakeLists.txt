cmake_minimum_required(VERSION 3.0)
add_executable(serdestest
   serdestest.cpp)

#target_include_directories(serdestest PUBLIC 
#   include)

target_link_libraries(serdestest
   wdb
   tcb
   ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS serdestest DESTINATION bin)

