link_directories($ENV{MSCBSYS}/lib/)

add_library(tcb
   TCBLib.cpp)

message ($ENV{MSCBSYS})

target_include_directories(tcb PRIVATE $ENV{MSCBSYS}/include)

add_executable(tcb_cl
   tcb_cl.cpp)

target_include_directories(tcb_cl PUBLIC $ENV{MSCBSYS}/include)


target_link_libraries(tcb_cl tcb mscb)

install(TARGETS tcb_cl DESTINATION bin)
install(TARGETS tcb
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

