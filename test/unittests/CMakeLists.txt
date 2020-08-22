file(GLOB_RECURSE CORE_TEST_SOURCES "*.cpp")

add_executable(tmp "${CORE_TEST_SOURCES}")

target_link_libraries(tmp core gtest gtest_main)
add_test(core tmp)