cmake_minimum_required(VERSION 3.0)
project(wds)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

find_package(Threads)

add_subdirectory(read_binary)

add_definitions(-DWD2_DONT_INCLUDE_REG_ACCESS_VARS)

add_custom_target(register_map_wd2
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/../firmware/WD2/wd2_sys_ctrl/wd2_xsdk_workspace/wd2_app_sw/common/src/register_map_wd2.h ${CMAKE_SOURCE_DIR}/src/register_map_wd2.h
)

add_library(wdb
   src/WDBLib.cpp
   src/averager.cpp)

target_include_directories(wdb PRIVATE wds/src include mxml)

add_executable(wds
   wds/src/mongoose.c
   mxml/mxml.cxx
   mxml/strlcpy.cxx
   wds/src/wds.cpp)

target_include_directories(wds PUBLIC wds/src include mxml)
target_link_libraries(wds wdb ${CMAKE_THREAD_LIBS_INIT})
add_dependencies(wds register_map_wd2)
add_dependencies(wdb register_map_wd2)

install(TARGETS wds DESTINATION bin)
install(TARGETS wdb
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

