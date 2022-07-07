#./CMakeLists.txt
#
#

cmake_minimum_required(VERSION 3.22.1)

project(hello_world VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
 

option(TEST "build" ON)
option(BUILD_EXAMPLES "build" ON)

if(TEST)
    add_subdirectory(test)
endif(TEST)




if(BUILD_EXAMPLES)

    file (GLOB EXAMPLES "examples/*.cpp" )

    foreach(EACH IN LISTS EXAMPLES)
        get_filename_component(TARGET ${EACH} NAME_WE  )
        add_executable(${TARGET} ${EACH})
        target_include_directories(${TARGET}  PUBLIC source)
        message(STATUS "X=${TARGET}")
    endforeach()
 
endif(BUILD_EXAMPLES)
