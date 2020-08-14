include_directories(SYSTEM    
    ${PROJECT_SOURCE_DIR}/cpp-sc2/include
    ${PROJECT_SOURCE_DIR}/cpp-sc2/contrib/protobuf/src
    ${PROJECT_BINARY_DIR}/cpp-sc2/generated
    "."
)

link_directories(${PROJECT_BINARY_DIR}/cpp-sc2/bin)

add_subdirectory("core")
add_subdirectory("runners")