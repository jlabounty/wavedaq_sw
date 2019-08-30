cmake_minimum_required(VERSION 2.8)

set(CMAKE_INSTALL_PREFIX /)

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

add_executable(dcbc src/dcbc.c ${SRC})
add_executable(wdbc src/wdbc.c ${SRC})
add_executable(dcbs src/dcbs.c ${SRC})

target_compile_options(dcbc PRIVATE -D LINUX_COMPILE)
target_compile_options(wdbc PRIVATE -D LINUX_COMPILE)
target_compile_options(dcbs PRIVATE -D LINUX_COMPILE)
target_link_libraries(dcbc readline)
target_link_libraries(wdbc readline)

install(TARGETS dcbc wdbc dcbs DESTINATION bin)