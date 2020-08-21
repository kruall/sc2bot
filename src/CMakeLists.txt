include_directories(SYSTEM    
    ${CPPSC2_SOURCE_DIR}/include
    ${CPPSC2_SOURCE_DIR}/contrib/protobuf/src
    ${CPPSC2_BINARY_DIR}/generated
    "."
)

link_directories(${CPPSC2_BINARY_DIR}/bin)

add_subdirectory("core")
add_subdirectory("runners")