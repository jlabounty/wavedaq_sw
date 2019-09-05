cmake_minimum_required(VERSION 2.8)

set(CMAKE_INSTALL_PREFIX /)

#
# generate git-revision.h
#
find_package(Git)
set(GIT_REVISION ${PROJECT_SOURCE_DIR}/../../include/git-revision.h)
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
   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/../../include/
)

#
# source files for executables
#
set(SRC
   src/system.c
   src/cmd_processor.c
   src/wd2_config.c
   src/sc_io.c
   src/spi_bpl.c
   src/xspi.c
   src/xspi_g.c
   src/xspi_options.c
   src/xspi_selftest.c
   src/xspi_sinit.c
   src/drv_axi_dcb_reg_bank.c
   src/mod_crate_com.c
   src/mod_reg_access.c
   src/dbg.c
   src/utilities.c
)

add_executable(dcbi src/dcbi.c ${SRC})
add_executable(dcbc src/dcbc.c ${SRC})
add_executable(wdbc src/wdbc.c ${SRC})
add_executable(dcbs src/dcbs.c ${SRC})

target_include_directories(dcbs PRIVATE ${PROJECT_SOURCE_DIR}/../../include)

target_compile_options(dcbi PRIVATE -D LINUX_COMPILE)
target_compile_options(dcbc PRIVATE -D LINUX_COMPILE)
target_compile_options(wdbc PRIVATE -D LINUX_COMPILE)
target_compile_options(dcbs PRIVATE -D LINUX_COMPILE)

#
# libraries
#
target_link_libraries(dcbi readline)
target_link_libraries(dcbc readline)
target_link_libraries(wdbc readline)

add_dependencies(dcbs git_revision_h)

install(TARGETS dcbi dcbc wdbc dcbs DESTINATION bin)