file(GLOB_RECURSE CORE_SOURCES "*.cpp" "*.h")
add_library(core ${CORE_SOURCES})

target_link_libraries(core
    sc2api sc2lib sc2utils sc2protocol civetweb libprotobuf
)