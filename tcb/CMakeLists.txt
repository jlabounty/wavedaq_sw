cmake_minimum_required(VERSION 3.0)
add_executable(tcb_cl
   tcb_cl.cpp)

#target_include_directories(tcb_cl PUBLIC 
#   )

target_link_libraries(tcb_cl
   mxml
   mscb
   tcb
   dcb
   wdb
   ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS tcb_cl DESTINATION bin)

