cmake_minimum_required(VERSION 3.22)

project(memory)

file(GLOB SOURCES
    "src/*.h"
    "src/*.cpp"
)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} ${SOURCES})

# include_directories(../)
target_include_directories(memory PUBLIC include/)

target_link_libraries(memory PRIVATE spdlog)

add_subdirectory(thirdparty)
add_subdirectory(test)
add_subdirectory(perf)

add_test(NAME perf COMMAND perf_test)
add_test(NAME test COMMAND unit_test)