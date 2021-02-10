cmake_minimum_required(VERSION 3.0)
add_executable(wds
   src/mongoose.c
   src/wds.cpp)

target_include_directories(wds PUBLIC 
   src 
   ../../)

target_link_libraries(wds
   mxml
   wdb
   dcb
   ${CMAKE_THREAD_LIBS_INIT})

add_dependencies(wds git_revision_h)

install(TARGETS wds DESTINATION bin)

#
# Install if executed on a DCB
#
install(TARGETS wds DESTINATION /fw_sw/dcb/prod)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/wds/html 
   DESTINATION /fw_sw/dcb/prod)
install(PROGRAMS wds.sh DESTINATION /etc/init.d/)
install(CODE "execute_process(COMMAND /etc/init.d/wds.sh restart TIMEOUT 3)")