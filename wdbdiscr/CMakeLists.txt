cmake_minimum_required(VERSION 3.0)
add_executable(wdbdiscr
   wdbdiscr.cpp)

target_link_libraries(wdbdiscr
   wdb
   ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS wdbdiscr DESTINATION bin)
