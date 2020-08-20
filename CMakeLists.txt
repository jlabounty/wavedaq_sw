cmake_minimum_required(VERSION 3.0)
project(wdaq)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

# suppress warnings due to compiler bug on ARM targets
if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
   set(CMAKE_CXX_FLAGS "-Wno-psabi")
endif()

find_package(Threads)

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
#message(STATUS "CXX FLAGS: ${CMAKE_CXX_FLAGS}")
#message(STATUS "CXX FLAGS release: ${CMAKE_CXX_FLAGS_RELEASE}")

#
# generate git-revision.h
#
find_package(Git)
set(GIT_REVISION ${PROJECT_SOURCE_DIR}/git-revision.h)
set(GIT_REVISION_TMP ${GIT_REVISION}.tmp)

add_custom_target(git_revision_h
   COMMAND ${CMAKE_COMMAND} -E echo_append "\\#define GIT_REVISION \\\"" > ${GIT_REVISION_TMP}
   COMMAND ${GIT_EXECUTABLE} log -n 1 --pretty=format:"%ad" >> ${GIT_REVISION_TMP}
   COMMAND ${CMAKE_COMMAND} -E echo_append " - " >> ${GIT_REVISION_TMP}
   COMMAND ${GIT_EXECUTABLE} log -n 1 --pretty=format:"%h" >> ${GIT_REVISION_TMP}
   COMMAND ${CMAKE_COMMAND} -E echo_append " on branch " >> ${GIT_REVISION_TMP}
   COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD  | tr -d '\\n' >> ${GIT_REVISION_TMP}
   COMMAND ${CMAKE_COMMAND} -E echo \\\" >> ${GIT_REVISION_TMP}
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GIT_REVISION_TMP} ${GIT_REVISION}
   COMMAND ${CMAKE_COMMAND} -E remove ${GIT_REVISION_TMP}
)


#
# Check for mxml
#
if (NOT EXISTS ${PROJECT_SOURCE_DIR}/mxml/.git)
   message(FATAL_ERROR "mxml files not found, please make sure git submodules are downloaded.\n"
                       "generation aborted\n\n")
endif()

#
# Check for mscb
#
if (EXISTS ${PROJECT_SOURCE_DIR}/mscb/.git)
   add_subdirectory(mscb)
   set(HAVE_MSCB on)
else()
   message(WARNING "mscb files not found, please make sure git submodules are downloaded.\n"
                   "generation of TCB and other libs inhibited\n\n")
   set(HAVE_MSCB off)
endif()

   #add_subdirectory(read_binary)

# definitions to remove hardware access in WDBReg.h and DCBReg.h
add_definitions(-DWD2_DONT_INCLUDE_REG_ACCESS_VARS -DDCB_DONT_INCLUDE_REG_ACCESS_VARS -DDCB_DONT_INCLUDE_VARS)

#
# MXML Library
#
add_library(mxml
  mxml/mxml.cxx
  mxml/strlcpy.cxx)

target_include_directories(mxml PUBLIC 
   mxml)

install(TARGETS mxml
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

#
# DCB Library
#
add_library(dcb
   src/DCBLib.cpp)

target_compile_definitions(dcb
   PUBLIC -DDCB_DONT_INCLUDE_REG_ACCESS_VAR
   PUBLIC -DDCB_DONT_INCLUDE_VARS)

target_include_directories(dcb PUBLIC 
   dcb/app/src/
   include)

install(TARGETS dcb
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

#
# WDB Library
#
add_library(wdb
   src/WDBLib.cpp
   src/averager.cpp)

add_dependencies(wdb git_revision_h)

target_compile_definitions(wdb
   PUBLIC -DWD2_DONT_INCLUDE_REG_ACCESS_VARS)

target_include_directories(wdb PUBLIC 
   ./
   wds/src
   include)

target_link_libraries(wdb
   mxml
   dcb)

install(TARGETS wdb
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

#
# TCB Library
#
add_library(tcb
   src/TCBLib.cpp
   src/averager.cpp)

target_include_directories(tcb PUBLIC 
   include)

target_link_libraries(tcb
   mscb
   mxml
   dcb)

install(TARGETS tcb
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

#
# WDAQ Library
#
add_library(wdaq
   src/DAQLib.cpp
   src/WDLib.cpp
   src/WDAQLib.cpp)

target_include_directories(wdaq PUBLIC
   include)

target_link_libraries(wdaq
   mxml
   mscb
   wdb
   tcb
   dcb)

install(TARGETS wdaq
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

#
# subdirectories
#
add_subdirectory(wds)

add_subdirectory(tcb)

add_subdirectory(wd_cl)

add_subdirectory(serdestest)

add_subdirectory(wdbdiscr)

# disable targets that requires libmscb
if(NOT TARGET mscb)
   set_target_properties(tcb wdaq tcb_cl wd_cl serdestest PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
endif()

