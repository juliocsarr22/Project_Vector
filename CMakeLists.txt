cmake_minimum_required(VERSION 3.5)
project (Vector)

find_package(GTest REQUIRED)
include_directories( ${GTEST_INCLUDE_DIRS})

set( GCC_COMPILE_FLAGS "-Wall" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )

include_directories(include)

file(GLOB SOURCES_TEST "test/*.cpp" )

add_executable(ex ${SOURCES_TEST} )
