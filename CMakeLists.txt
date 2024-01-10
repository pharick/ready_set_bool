cmake_minimum_required(VERSION 3.27)
project(ready_set_bool)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_library(ready_set_bool STATIC ${SOURCES})

find_package(Catch2 REQUIRED)
file(GLOB TEST_SOURCES "tests/test_*.cpp")
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain ready_set_bool)

include(CTest)
include(Catch)
catch_discover_tests(tests)
