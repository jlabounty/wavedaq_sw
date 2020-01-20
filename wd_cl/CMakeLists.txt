cmake_minimum_required(VERSION 3.0)
add_executable(wd_cl
   wd_cl.cpp)

#target_include_directories(wd_cl PUBLIC 
#   include)

target_link_libraries(wd_cl
   wdaq
   ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS wd_cl DESTINATION bin)

