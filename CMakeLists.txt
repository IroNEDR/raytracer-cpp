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
add_library(matrix INTERFACE include/matrix.hpp)
add_library(transform src/transform.cpp include/transform.hpp)
add_library(ray src/ray.cpp include/ray.hpp)
add_library(sphere src/sphere.cpp include/sphere.hpp)

add_executable(rt_default apps/default/main.cpp)
add_executable(rt_projectile apps/projectile/main.cpp)
add_executable(rt_clock apps/clock/main.cpp)

target_link_libraries(rt_projectile tuple utils color canvas)
target_include_directories(rt_projectile PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(rt_clock tuple utils color canvas transform matrix)
target_include_directories(rt_clock PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(tests)


