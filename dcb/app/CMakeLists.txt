cmake_minimum_required(VERSION 2.8)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

#
# generate git-revision.h
#
find_package(Git)
set(GIT_REVISION ${PROJECT_SOURCE_DIR}/../../../git-revision.h)
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
   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

#
# source files for all executable to be put in library
#
set(LIBSRC
   src/system.c
   src/cmd_processor.c
   src/wd2_config.c
   src/sc_io.c
   src/drv_bpl.c
   src/register_map_dcb.c
   src/drv_axi_dcb_reg_bank.c
   src/drv_spi_if.c
   src/drv_lmk.c
   src/drv_si5324.c
   src/drv_sys_mon.c
   src/drv_qspi_flash.c
   src/mod_crate_com.c
   src/mod_reg_access.c
   src/mod_status.c
   src/mod_system_management.c
   src/crc32.c
   src/dbg.c
   src/utilities.c
   src/update_config.c
)

set(PROGS
   dcbi
   dcbc
   sltc
   dcbs
   upload
)

# libray
add_library(dcblib STATIC ${LIBSRC})
target_include_directories(dcblib PUBLIC
      ${PROJECT_SOURCE_DIR}/../../../include
      ${PROJECT_SOURCE_DIR}/../../../)
target_compile_definitions(dcblib PUBLIC LINUX_COMPILE)
add_dependencies(dcblib git_revision_h)

# executables
foreach(PROG ${PROGS})
   add_executable(${PROG} src/${PROG})
   target_link_libraries(${PROG} dcblib readline)   
endforeach()

install(TARGETS ${PROGS} DESTINATION bin)