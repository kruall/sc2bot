file(GLOB_RECURSE BOT_SOURCES "*.cpp" "*.h")

include_directories(SYSTEM
    "."
)

link_directories(${PROJECT_BINARY_DIR}/cpp-sc2/bin)

add_executable(sc2bot ${BOT_SOURCES})
target_link_libraries(sc2bot
    sc2api sc2lib sc2utils sc2protocol civetweb libprotobuf
)