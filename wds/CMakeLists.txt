cmake_minimum_required(VERSION 3.14)
project(wds)

set(CMAKE_CXX_STANDARD 11)

include_directories(src ../lib)
include_directories(../../firmware/WD2/wd2_sys_ctrl/wd2_xsdk_workspace/wd2_app_sw/common/src/)

add_definitions(-DWD2_DONT_INCLUDE_REG_ACCESS_VARS)

add_executable(wds
        src/mongoose.c
        src/mongoose.h
        src/mxml.c
        src/mxml.h
        src/strlcpy.c
        src/strlcpy.h
        src/wds.cpp
        src/wds.h
        ../lib/WDBLib.cpp
        ../lib/WDBLib.h
        ../lib/averager.cpp
        ../lib/averager.h)
