cmake_minimum_required(VERSION 3.0)
project(serdestest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

find_package(Threads)

if (NOT EXISTS $ENV{MSCBSYS}/src/mscb.cxx)
      message(FATAL_ERROR "\nError: 'mscb' submodule not found. Please install\n"
      "in git root directory. Serdestest won't be built\n\n")
endif()

link_directories($ENV{MSCBSYS}/lib/)

add_definitions(-DWD2_DONT_INCLUDE_REG_ACCESS_VARS -DDCB_DONT_INCLUDE_REG_ACCESS_VARS)

add_library(serdestestlib
   ../tcb/TCBLib.cpp
   ../src/WDBLib.cpp
   ../src/DCBLib.cpp
   ../src/averager.cpp)

target_include_directories(serdestestlib PUBLIC 
   ../include 
   ../mxml 
   ../tcb 
   ../dcb/app/src/
   $ENV{MSCBSYS}/include)

add_executable(serdestest
   ../mxml/mxml.cxx
   ../mxml/strlcpy.cxx
   serdestest.cpp)

target_include_directories(serdestest PUBLIC  ../include ../mxml ../tcb $ENV{MSCBSYS}/include)

target_link_libraries(serdestest serdestestlib mscb ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS serdestest DESTINATION bin)
install(TARGETS serdestestlib
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

