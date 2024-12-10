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

include_directories(include)
add_library(utils src/utils.cpp include/utils.hpp)
add_library(tuple src/tuple.cpp include/tuple.hpp)
add_library(color src/color.cpp include/color.hpp)
add_library(canvas src/canvas.cpp include/canvas.hpp)
add_executable(rt apps/main.cpp)

add_subdirectory(tests)


