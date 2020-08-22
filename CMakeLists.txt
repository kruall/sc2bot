cmake_minimum_required(VERSION 3.1)

project(sc2bot)
set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(CPPSC2_SOURCE_DIR "${PROJECT_SOURCE_DIR}/contrib/cpp-sc2")
set(CPPSC2_BINARY_DIR "${PROJECT_BINARY_DIR}/contrib/cpp-sc2")

set(BUILD_API_TESTS OFF CACHE INTERNAL "" FORCE)
set(BUILD_API_EXAMPLES OFF CACHE INTERNAL "" FORCE)
set(CMAKE_BUILD_TYPE "Release" CACHE INTERNAL "" FORCE)

set(BENCHMARK_SOURCE_DIR "${PROJECT_SOURCE_DIR}/contrib/google/benchmark")

include_directories(SYSTEM    
    ${CPPSC2_SOURCE_DIR}/include
    ${CPPSC2_SOURCE_DIR}/contrib/protobuf/src
    ${CPPSC2_BINARY_DIR}/generated
    "./src"
)

link_directories(${CPPSC2_BINARY_DIR}/bin)

add_subdirectory("contrib/cpp-sc2")
add_subdirectory("contrib/google/googletest")
add_subdirectory("contrib/google/benchmark")
add_subdirectory("src")
add_subdirectory("test")