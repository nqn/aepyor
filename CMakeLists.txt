cmake_minimum_required (VERSION 2.6)
project("Aepyornithidae")

# gtest
ADD_SUBDIRECTORY (dependencies/gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# tests
add_executable(aepyor-tests src/tests/test.cc)
target_link_libraries(aepyor-tests gtest gtest_main)
add_test(aepyor-tests aepyor-tests)

add_executable(aepyor src/main.cc)