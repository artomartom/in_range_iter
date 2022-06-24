#./CMakeLists.txt
#
#

cmake_minimum_required(VERSION 3.22.1)

project(hello_world VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

file (GLOB SOURCES "./source/*.cpp" )
add_executable(${PROJECT_NAME} ${SOURCES} )

add_subdirectory(./source/hello)


add_subdirectory(test)