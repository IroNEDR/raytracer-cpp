include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(TestRunner tuple_test.cpp)
target_link_libraries(TestRunner GTest::gtest_main tuple utils)
target_include_directories(TestRunner PRIVATE ${PROJECT_SOURCE_DIR}/includes)
include(GoogleTest)
gtest_discover_tests(TestRunner)
