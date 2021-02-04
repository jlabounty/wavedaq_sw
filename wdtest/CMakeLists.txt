cmake_minimum_required(VERSION 3.0)

add_executable(wdtest wdtest.cpp)

target_include_directories(wdtest PUBLIC ../../)

target_link_libraries(wdtest
   mxml
   wdb
   dcb
   ${CMAKE_THREAD_LIBS_INIT})
