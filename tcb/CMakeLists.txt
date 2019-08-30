cmake_minimum_required(VERSION 3.0)
project(tcb)

if (NOT EXISTS $ENV{MSCBSYS}/src/mscb.cxx)
      message(FATAL_ERROR "\nError: 'mscb' submodule not found. Please install\n"
      "in git root directory. TCB library and executables won't be built\n\n"
   )
endif()

link_directories($ENV{MSCBSYS}/lib/)

add_library(tcb
   TCBLib.cpp)

target_include_directories(tcb PRIVATE $ENV{MSCBSYS}/include)

add_executable(tcb_cl
   tcb_cl.cpp)

target_include_directories(tcb_cl PUBLIC $ENV{MSCBSYS}/include)


target_link_libraries(tcb_cl tcb mscb)

install(TARGETS tcb_cl DESTINATION bin)
install(TARGETS tcb
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

