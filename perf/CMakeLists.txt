cmake_minimum_required(VERSION 3.22)

project(perf_test)

add_executable(${PROJECT_NAME} perf.cpp)

target_link_libraries(${PROJECT_NAME} benchmark memory)