cmake_minimum_required(VERSION 3.30)
project(RayTracer)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++23")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(includes)
add_library(utils src/utils.cpp includes/utils.hpp)
add_library(tuple src/tuple.cpp includes/tuple.hpp)
add_executable(rt apps/main.cpp)

add_subdirectory(tests)


