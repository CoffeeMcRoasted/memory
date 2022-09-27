cmake_minimum_required(VERSION 3.22)

project(unit_test)

add_executable(${PROJECT_NAME} test.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE gtest spdlog memory)