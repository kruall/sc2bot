add_executable(hello_world hello_world.cpp)

target_link_libraries(hello_world
    sc2api sc2lib sc2utils sc2protocol civetweb libprotobuf
    core
)

add_executable(no_vespen no_vespen.cpp)

target_link_libraries(no_vespen
    sc2api sc2lib sc2utils sc2protocol civetweb libprotobuf
    core
)