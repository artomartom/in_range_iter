#./test/CMakeLists.txt
#
#
cmake_minimum_required(VERSION 3.5)

enable_testing()
find_package(GTest CONFIG  )

if(GTest_FOUND)

add_executable(UNIT_TEST test.cpp)
target_link_libraries(UNIT_TEST gtest_main)
target_link_libraries(UNIT_TEST gtest)
target_include_directories(UNIT_TEST  PUBLIC ../source)
add_test(NAME UNIT_TEST COMMAND UNIT_TEST)
endif()