cmake_minimum_required(VERSION 3.14)
project(wds)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

add_subdirectory(read_binary)

add_definitions(-DWD2_DONT_INCLUDE_REG_ACCESS_VARS)

add_library(wdb lib/WDBLib.cpp lib/averager.cpp)
target_include_directories(wdb PRIVATE wds/src ../firmware/WD2/wd2_sys_ctrl/wd2_xsdk_workspace/wd2_app_sw/common/src/)

add_executable(wds
        wds/src/mongoose.c
        wds/src/mxml.c
        wds/src/mxml.h
        wds/src/strlcpy.c
        wds/src/strlcpy.h
        wds/src/wds.cpp)

target_include_directories(wds PUBLIC wds/src lib ../firmware/WD2/wd2_sys_ctrl/wd2_xsdk_workspace/wd2_app_sw/common/src/)

target_link_libraries(wds wdb)

install(TARGETS wds DESTINATION bin)
install(TARGETS wdb
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

