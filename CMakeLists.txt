cmake_minimum_required(VERSION 3.1)

project(sc2bot)
set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(CPPSC2_SOURCE_DIR "${PROJECT_SOURCE_DIR}/contrib/cpp-sc2")
set(CPPSC2_BINARY_DIR "${PROJECT_BINARY_DIR}/contrib/cpp-sc2")

add_subdirectory("contrib/cpp-sc2")
add_subdirectory("src")