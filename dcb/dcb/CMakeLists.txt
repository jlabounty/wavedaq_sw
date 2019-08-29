cmake_minimum_required(VERSION 2.8)

set(CMAKE_INSTALL_PREFIX /)

add_executable(dcb
   src/app_dcb_ctrl.c
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

target_compile_options(dcb PRIVATE -D LINUX_COMPILE)
target_link_libraries(dcb readline)

install(TARGETS dcb DESTINATION bin)