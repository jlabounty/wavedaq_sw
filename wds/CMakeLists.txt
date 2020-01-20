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
